var clickX = new Array();
var clickY = new Array();
var clickDrag = new Array();
var paint;
var context;
var canvas;

function addClick(x, y, dragging)
{
    clickX.push(x);
    clickY.push(y);
    clickDrag.push(dragging);
}

function redraw(){
    context.clearRect(0, 0, context.canvas.width, context.canvas.height); // Clears the canvas

    context.strokeStyle = "#1e88e5";
    context.lineJoin = "round";
    context.lineWidth = Math.round(document.getElementById("drawingCanvas").clientWidth/15);

    for(var i=0; i < clickX.length; i++) {
        context.beginPath();
        if(clickDrag[i] && i){
            context.moveTo(clickX[i-1], clickY[i-1]);
        }else{
            context.moveTo(clickX[i]-1, clickY[i]);
        }
        context.lineTo(clickX[i], clickY[i]);
        context.closePath();
        context.stroke();
    }
}

function prepareCanvas() {

    document.getElementById('drawingCanvas').setAttribute('width', document.getElementById("drawingCanvas").clientWidth);
    document.getElementById('drawingCanvas').setAttribute('height', document.getElementById("drawingCanvas").clientHeight);
    context = document.getElementById('drawingCanvas').getContext("2d");
    canvas = document.getElementById("drawingCanvas");

    function press(e){
        var canvasEl = document.getElementById("drawingCanvas")
        var mouseX = e.pageX - canvasEl.offsetLeft;
        var mouseY = e.pageY - canvasEl.offsetTop;

        paint = true;
        addClick(e.pageX - canvasEl.offsetLeft, e.pageY - canvasEl.offsetTop);
        redraw();
    }

    function move(e) {
        var canvasEl = document.getElementById("drawingCanvas")
        if(paint){
            addClick(e.pageX - canvasEl.offsetLeft, e.pageY - canvasEl.offsetTop, true);
            redraw();
        }
    }

    function free(e){
        paint = false;
    }

    var obj = document.getElementById('drawingCanvas');
    obj.addEventListener('mousedown', press);
    obj.addEventListener('mousemove', move);
    obj.addEventListener('mouseup', free);
    obj.addEventListener('mouseleave', function(e) {
            paint = false;
    });

    document.body.addEventListener("touchstart", function (e) {
        if (e.target == canvas) {
            e.preventDefault();
            press(e);
        }
    }, {passive: false});
    document.body.addEventListener("touchend", function (e) {
        if (e.target == canvas) {
            e.preventDefault();
            free(e);
        }
    }, {passive: false});
    document.body.addEventListener("touchmove", function (e) {
        if (e.target == canvas) {
            e.preventDefault();
            move(e);
        }
    }, {passive: false});

    var btn_run = document.getElementById('btn_run');
    var btn_back = document.getElementById('btn_back');
    var btn_left = document.getElementById('btn_left');
    var btn_right = document.getElementById('btn_right');
    var btn_stop = document.getElementById('btn_stop');

    btn_run.addEventListener('mousedown', robot_run);
    btn_run.addEventListener('mouseup', robot_stop);

    btn_back.addEventListener('mousedown', robot_back);
    btn_back.addEventListener('mouseup', robot_stop);

    btn_left.addEventListener('mousedown', robot_left);
    btn_left.addEventListener('mouseup', robot_stop);

    btn_right.addEventListener('mousedown', robot_right);
    btn_right.addEventListener('mouseup', robot_stop);

    btn_stop.addEventListener('mousedown', robot_stop);

    var obtn_run = document.getElementById('obtn_run');
    var obtn_back = document.getElementById('obtn_back');
    var obtn_left = document.getElementById('obtn_left');
    var obtn_right = document.getElementById('obtn_right');
    var obtn_stop = document.getElementById('obtn_stop');

    obtn_run.addEventListener('mousedown', orobot_run);
    obtn_run.addEventListener('mouseup', orobot_stop);

    obtn_back.addEventListener('mousedown', orobot_back);
    obtn_back.addEventListener('mouseup', orobot_stop);

    obtn_left.addEventListener('mousedown', orobot_left);
    obtn_left.addEventListener('mouseup', orobot_stop);

    obtn_right.addEventListener('mousedown', orobot_right);
    obtn_right.addEventListener('mouseup', orobot_stop);

    obtn_stop.addEventListener('mousedown', orobot_stop);

}

function clearCanvas() {
    context.clearRect(0, 0, context.canvas.width, context.canvas.height);
    clickX = new Array();
    clickY = new Array();
    clickDrag = new Array();
    paint = false;
}

function recognizeDigit() {
    var imgSrc = canvas.toDataURL();
    var auxCanvas = document.getElementById("auxCanvas");
    auxCanvas.setAttribute('width', 28);
    auxCanvas.setAttribute('height', 28);
    var auxContext = auxCanvas.getContext('2d');
    var auxImage = new Image();
    auxImage.src = imgSrc;
    auxImage.onload = function(){
        auxContext.drawImage(auxImage, 0, 0, context.canvas.width, context.canvas.height, 0, 0, 28, 28);
        var canvasData  = auxContext.getImageData(0, 0, 28, 28).data;
        // console.log(String(prepareModelData(canvasData)));
        console.log()
        var url = window.location.href+ "cgi-bin/mnist?img=" + String(prepareModelData(canvasData)).replace(/,/g, '');
        var xmlHttp = new XMLHttpRequest();
        console.log(url);
        xmlHttp.onreadystatechange = function() {
            if (xmlHttp.status == 200){
                if(xmlHttp.responseText) {
                    alert(xmlHttp.responseText);
                    console.log(xmlHttp.responseText);
                }
            }
            else{
                // alert('Error');
            }
        }
        xmlHttp.open("GET", url, true); // true for asynchronous
        xmlHttp.send(null);
    }
}

function prepareModelData(canvasData) {
    var imageBinary = [];
    for (var pixelInd = 0; pixelInd < 28 * 28; pixelInd++) {
        let pixelSeriesInd = pixelInd * 4;
        if (canvasData[pixelSeriesInd] > 0 || canvasData[pixelSeriesInd+1] > 0|| canvasData[pixelSeriesInd+2] > 0) {
            imageBinary.push(1.0);
        } else {
            imageBinary.push(0.0);
        }
    }

    var modelData = [];
    for (var rowInd = 0; rowInd < 28; rowInd++) {
        var row = [];
        for (var colInd = 0; colInd < 28; colInd++) {
            row.push([imageBinary[rowInd * 28 + colInd]]);
        }
        modelData.push(row);
    }

    // var modelData = [];
    // for (var colInd = 0; colInd < 28; colInd++) {
    //     var col = [];
    //     for (var rowInd = 0; rowInd < 28; rowInd++) {
    //         col.push([imageBinary[rowInd * 28 + colInd]]);
    //     }
    //     modelData.push(col);
    // }

    return modelData;
}


function robot_run() {
    var url = window.location.href + "cgi-bin/robot_run";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function robot_back() {
    var url = window.location.href+ "cgi-bin/robot_back";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function robot_left() {
    var url = window.location.href+ "cgi-bin/robot_left";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function robot_right() {
    var url = window.location.href+ "cgi-bin/robot_right";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function robot_stop() {
    var url = window.location.href+ "cgi-bin/robot_stop";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function orobot_run() {
    var url = "http://192.168.199.199/robot_run";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function orobot_back() {
    var url = "http://192.168.199.199/robot_back";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function orobot_left() {
    var url = "http://192.168.199.199/robot_left";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function orobot_right() {
    var url = "http://192.168.199.199/robot_right";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

function orobot_stop() {
    var url = "http://192.168.199.199/robot_stop";
    var xmlHttp = new XMLHttpRequest();
    console.log(url);
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.status == 200){
            // alert(xmlHttp.responseText);
        }
        else{
            // alert('Error');
        }
    }
    xmlHttp.open("GET", url, true); // true for asynchronous
    xmlHttp.send(null);
}

/*
 * File      : wn_sample.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 * This software is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http://www.gnu.org/licenses/>.
 *
 * You are free to use this software under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively for commercial application, you can contact us
 * by email <business@rt-thread.com> for commercial license.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-26     ChenYong     First version
 */

#include <msh.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <onnx.h>
#include <webnet.h>
#include <wn_module.h>

#define ONNX_MODEL_NAME "mnist-sm.onnx"

// ASCII lib from (https://www.jianshu.com/p/1f58a0ebf5d9)
static const char codeLib[] = "@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.   ";
static void print_img(const float * buf)
{
    for(int y = 0; y < 28; y++) 
    {
        for (int x = 0; x < 28; x++) 
        {
            int index = 0; 
            if(buf[y*28+x] > 0.6f) index =69;
            if(index < 0) index = 0;
            printf("%c",codeLib[index]);
            printf("%c",codeLib[index]);
        }
        printf("\n");
    }
}

static void cgi_mnist_handler(struct webnet_session* session)
{
    const char* mimetype;
    struct webnet_request* request;

    RT_ASSERT(session != RT_NULL);
    request = session->request;
    RT_ASSERT(request != RT_NULL);

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", -1);

    if (request->query_counter)
    {
        const char *image_value;
        image_value = webnet_request_get_query(request, "img");
			  float* input = (float*) malloc(sizeof(int64_t)*28*28);
			  if(input == RT_NULL)
				{
					  static const char* err = "Out of Memory";
				    webnet_session_write(session, (const rt_uint8_t*)err, rt_strlen(err));
					  return;
				}
				for(int i = 0; i < 784; i++)
				{
				    if(image_value[i] == '0')
						{
						    input[i] = 0.0;
						}
						else
						{
						    input[i] = 1.0;
						}
				}
				print_img(input);
				printf("\n");

				// 0. Load Model
				Onnx__ModelProto* model = onnx_load_model(ONNX_MODEL_NAME);
				if(model == NULL)
				{
					  static const char* err = "Failed to load model";
				    webnet_session_write(session, (const rt_uint8_t*)err, rt_strlen(err));
					  return;
				}

				// 1. Initialize input
				int64_t* shapeInput = (int64_t*) malloc(sizeof(int64_t)*3);
				shapeInput[0] = 28; shapeInput[1] = 28; shapeInput[2] =  1;

				// 2. Run Model
				float* output = onnx_model_run(model, input, shapeInput);

				// 3. Print Result
				float max = 0;
				rt_uint8_t max_index = 0;
				printf("\nPredictions: \n");
				for(int i = 0; i < 10; i++)
				{
						printf("%f ", output[i]);
						if(output[i] > max)
						{
								max = output[i];
								max_index = i;
						}
				}
				char ret[2];
				sprintf(ret,"%d", max_index);
        webnet_session_write(session, ret, 1);
				printf("\n");
				printf("\nThe number is %d\n", max_index);

				// 4. Free model
				free(shapeInput);
				free(output);
				onnx__model_proto__free_unpacked(model, NULL);
    }
    // webnet_session_printf(session, body, a, b, a + b);
}

static void cgi_robot_run_handler(struct webnet_session* session)
{
    msh_exec("robot_run", rt_strlen("robot_run"));
    const char* mimetype;
    static const char* status = "ok";

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));
		webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

static void cgi_robot_back_handler(struct webnet_session* session)
{
    msh_exec("robot_back", rt_strlen("robot_back"));
    const char* mimetype;
    static const char* status = "ok";

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));
    webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

static void cgi_robot_left_handler(struct webnet_session* session)
{
    msh_exec("robot_left", rt_strlen("robot_left"));
    const char* mimetype;
    static const char* status = "ok";

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));
    webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

static void cgi_robot_right_handler(struct webnet_session* session)
{
    msh_exec("robot_right", rt_strlen("robot_right"));
    const char* mimetype;
    static const char* status = "ok";

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));
    webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

static void cgi_robot_stop_handler(struct webnet_session* session)
{
    msh_exec("robot_stop", rt_strlen("robot_stop"));
    const char* mimetype;
    static const char* status = "ok";

    /* get mimetype */
    mimetype = mime_get_type(".txt");

    /* set http header */
    session->request->result_code = 200;
    webnet_session_set_header(session, mimetype, 200, "Ok", strlen(status));
    webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
    // webnet_session_write(session, (const rt_uint8_t*)status, rt_strlen(status));
}

void webnet_test(void)
{
#ifdef WEBNET_USING_CGI
	  webnet_cgi_register("mnist", cgi_mnist_handler);
	  webnet_cgi_register("robot_run", cgi_robot_run_handler);
	  webnet_cgi_register("robot_back", cgi_robot_back_handler);
	  webnet_cgi_register("robot_left", cgi_robot_left_handler);
	  webnet_cgi_register("robot_right", cgi_robot_right_handler);
  	webnet_cgi_register("robot_stop", cgi_robot_stop_handler);
#endif

#ifdef WEBNET_USING_ALIAS
    webnet_alias_set("/test", "/admin");
#endif

#ifdef WEBNET_USING_AUTH
    webnet_auth_set("/admin", "admin:admin");
#endif

#ifdef WEBNET_USING_UPLOAD
    extern const struct webnet_module_upload_entry upload_entry_upload;

    webnet_upload_add(&upload_entry_upload);
#endif

    webnet_init();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(webnet_test, wenbet test);
#endif

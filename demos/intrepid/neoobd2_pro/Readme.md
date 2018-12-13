# Directory Structure

All the samples in this SDK follow almost the same structure and is being highlighted here because, keeping the directories `vspy` and `ti` in this *same path* for all demos, is important. This directory structure is adopted from Amazon FreeRTOS demos and user should stick to this structure as far as possible 

````C
aws-mqtt								 /* Parent folder for demo projects */
|   .ccsproject
|   .cproject
|   .project
|   Readme.md
|         
+---config_files						 /* Configuration headers (for freeRTOS, wifi-credentials, 
|											demo-specific configuration, etc.) */
|       aws_bufferpool_config.h
|       aws_demo_config.h
|       aws_mqtt_agent_config.h
|       aws_mqtt_config.h
|       aws_secure_sockets_config.h
|       aws_wifi_config.h
|       FreeRTOSConfig.h
|       FreeRTOSIPConfig.h
|       
+---Debug                                 /* The output folder */
+---include								  /* All the application includes in one place */
|       aws_clientcredential.h
|       aws_clientcredential_keys.h
|       aws_demo.h
|       aws_demo_runner.h
|       aws_dev_mode_key_provisioning.h
|       aws_hello_world.h
|       aws_logging_task.h
|       
+---source                                /* Source files/application code for a demo project */
|       aws_demo_runner.c
|       aws_dev_mode_key_provisioning.c
|       aws_hello_world.c
|       aws_logging_task_dynamic_buffers.c
|       main.c
|              
+---ti                                    /* All the dependencies on TI's supplied SDK */
|       Board.h
|       CC3220SF_LAUNCHXL.c
|       CC3220SF_LAUNCHXL.h
|       CC3220SF_LAUNCHXL_FREERTOS.cmd
|       network_if.c
|       network_if.h
|       README.html
|       uart_term.c
|       uart_term.h
|       
\---vspy                                  /* ISM library and CCIF auto-generated files */
        obd2pro_wifi_cc32xx.c
        obd2pro_wifi_cc32xx.h
        obd2pro_wifi_cc32xx_ism.a
        obd2pro_wifi_cc32xx_ism.h
        SpyCCode.c
        types.h
        
        
````

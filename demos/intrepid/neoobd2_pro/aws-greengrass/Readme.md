This sample is only a slight modification of the default AWS Greengrass Discovery sample in Amazon FreeRTOS, all steps explained as follows:

1. The sample first uses the Greengrass discovery protocol to discover and connect to a Greengrass device.
2. Next, the sample creates a task that executes Intrepid Security Module (ISM) process.
3. Next, the sample creates a task that publishes host address information to topic 'freertos/demos/ggd' and transmits a CANFD message every 1 second.

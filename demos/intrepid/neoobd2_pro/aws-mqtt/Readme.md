This sample is only a slight modification of the default AWS double echo sample in Amazon FreeRTOS, all steps explained as follows:

1. The sample first subscribes and publishes to the same topic (freeRTOS/demos/eho). We use the same prvMQTTConnectAndPublishTask for publishing messages on the demo topic.
2. For each publish the same message is first echoed back to the client through broker in the MQTTCallback. 
3. Next we append ACK to the echoed message and publish it back to the broker once again. This makes the second echo and this time a message is published on MQTT as well as on the CAN network. You can view this transmitted message on Vehicle Spy. No previous configuration is required on vehicle Spy.
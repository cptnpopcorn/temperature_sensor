# Security keys and certificates

..are to be placed here, if **MQTT_USE_TLS** is enabled in the project configuration

* `ca.crt` - public CA key used to sign the MQTT brokers public key, enabling secure MQTT messaging
* `client.crt`, `client.key` - clients public, CA-certified key and clients private key, for (optional) client authentication enabled with **MQTT_TLS_CLIENT_AUTH**
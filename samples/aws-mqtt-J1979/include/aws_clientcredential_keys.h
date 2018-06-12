/*
* PEM-encoded client certificate
*
* Must include the PEM header and footer:
* "-----BEGIN CERTIFICATE-----"
* "...base64 data..."
* "-----END CERTIFICATE-----";
*/
char* clientcredentialCLIENT_CERTIFICATE_PEM;
/*
* PEM-encoded client private key.
*
* Must include the PEM header and footer:
* "-----BEGIN RSA PRIVATE KEY-----"
* "...base64 data..."
* "-----END RSA PRIVATE KEY-----";
*/
char* clientcredentialCLIENT_PRIVATE_KEY_PEM;


#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAJ2ivsB5vTV1lxWcDzP3Kx+UU16zMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODExMzAwNzQy\n"\
"MjVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDu+cU9rQ9HZXIuhdQB\n"\
"2cu4VupUGxk+LaboR9NOXo+JXZSOLFHQCNMUqEJvYXKJt/aEYKW6dyBnVqAVGcR0\n"\
"U+Nl7l3hsAszBESJ85E6RHXZcRvP5GG/gmdeexW9kgJn8jO8xkKLeogGG9GpdrYC\n"\
"1d0BPBDGRmDw6MoMpnYlTevMkazDavWHDCQT0Ry7mGhSpaQdt3vVMg2lQQjBv3Ec\n"\
"M3/mhou1lcnBSAk+I+B0797Nh3IMrUy65KB6LzEzTUld3p2cv1E91lmQItFSUvAv\n"\
"Rc6wQRZSNhACTN6yXQcN7lOgKiE6oN2HKfGzRMBLcTbaWQeO+aYB5NUQwgrvcrrJ\n"\
"bsqlAgMBAAGjYDBeMB8GA1UdIwQYMBaAFAaYF9y4BMzRjaC/xUkJpYN3wp6dMB0G\n"\
"A1UdDgQWBBTNjDR+y9V+OBTZNKDKtzQu5LN5RjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAMQc+1aU/ZFcy4B90fxI6MeFa\n"\
"hpDUd60eIzjRshOiCdNFrgw4Mld7/cWUy8wyrNGMkQXyXeXTvVguXYNLfrUx2taX\n"\
"fa3yL58i1QmdUKn+4m0nWTk1bmn1QhhQQQKhtg6qT0pot8DbIwEnHvQ1Kp73lvCI\n"\
"OnmQn1ceGuGarl8Yeoo8Hf6vYjlQPTrKJJYy7E186T5sk2b40MHmvMI0EQj0s990\n"\
"Ra4jX2bHR1qEhfQbvClzSlZ4WsYVreaqX/eQI6DmXw1T9cWmLwL5W16NT+Ya7RLr\n"\
"woe/kdLbzf0m/SEpV5mYv2r4zT/HA5Hny8qmx2lm9Oss7NYuRsS74cm+xNtXrQ==\n"\
"-----END CERTIFICATE-----"

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate 
 * Authority) of the client certificate is used by the server for routing the 
 * device's initial request. (The device client certificate must always be 
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html, 
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 * 
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  NULL

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEA7vnFPa0PR2VyLoXUAdnLuFbqVBsZPi2m6EfTTl6PiV2UjixR\n"\
"0AjTFKhCb2Fyibf2hGCluncgZ1agFRnEdFPjZe5d4bALMwREifOROkR12XEbz+Rh\n"\
"v4JnXnsVvZICZ/IzvMZCi3qIBhvRqXa2AtXdATwQxkZg8OjKDKZ2JU3rzJGsw2r1\n"\
"hwwkE9Ecu5hoUqWkHbd71TINpUEIwb9xHDN/5oaLtZXJwUgJPiPgdO/ezYdyDK1M\n"\
"uuSgei8xM01JXd6dnL9RPdZZkCLRUlLwL0XOsEEWUjYQAkzesl0HDe5ToCohOqDd\n"\
"hynxs0TAS3E22lkHjvmmAeTVEMIK73K6yW7KpQIDAQABAoIBAAMQIH8R4MhBfJ0s\n"\
"CfOcHwhV1NsPHdu2KhWAFi1C+QQBtw27c7D+6/Wv0morDZTGTtqTgoxJSpkIezTK\n"\
"B8KV8Kw1ye5Cm2IkA9zgylO83OXUlU6s1rPlr/1+BmFPpcg/Snp48BFpmKS7ZoyN\n"\
"gPe4VgTWCEECVevAkBZpa8o+nW8ZyI3fojsqmwMosKlunb+dSTz0EP245OTJ4/Hq\n"\
"NyqSm2e58ikhmRrhKaAL5NBf3HH/Mh5v2qeV/6EEUHaCPnA7wGJmre4cMKi/w9wP\n"\
"Rup9InDbqU8Ix07Opt6MQTxm/O3bW6Ape8tii+apDNCwtahyxyi1LVnFtTeBDTSE\n"\
"yy+vQwECgYEA+S+OF7ctyZOudlaEsofFismTYG+eYdWjzGh134Ybk4V5ympckhof\n"\
"4ITdX2YMmkObBV5nUmckpTHKYgkEchK8CAWiBQ6ux7Z4ZUf8yasj9V/WhOZJcE75\n"\
"x1GTfHnyU59ID2DuJgDbsB4JGwIJePhm9bGyshuiFqhEmJ+4c2N3WGkCgYEA9YK9\n"\
"I6nSt9RXH6cgJnvud7tcz0VOm3NWTrGekpCtQ3B8VRRwnLA32lYR0qcQH2auN8Od\n"\
"aqZyM6i3QOUxY/KyPmHC/LSaiQfcN6y7pMJJy0weU6XNbxCYEOrOe7/NRTtPVQtX\n"\
"TTPqgwsw1YSsgwPyMH9O29azNElSkE8eVKl8uN0CgYEAzHPkVjkJ7HarkpTyU7lq\n"\
"r7EsptduUD+GIdUjwb67KZM+loImagndVc4uBHQqqvgFXaZTiBzwyEnOEBnt99q/\n"\
"RKW6hgPCDEL/Dbq/AojU/CMiU/DPGMLz1kJsjJlR5qKt8VBKlgvmNN6wAeTt+L93\n"\
"WufuAo0BtS1i+wcxxBs8dOECgYAoYS9wnS7eM1t9BkTgb4PCR5u1L4YFRUwNt2MI\n"\
"YilNLUQVzj3TV5xoGb3msrmRIJdI7rCGaQfhfT9euhOMh89POU8TtzSvkw5iTdOy\n"\
"/o2alVNrmJqYSNdp+OSrL9m4KFAdAbeDKCXLFd0bUS36gnykA1xaBg8Fa4Xb3Fd1\n"\
"v0aXNQKBgE9jBubAlT9MpVXg3K97KvzGO76p5V8UiSQ2glg5QXfxNeMiiLrNZc+P\n"\
"Uwkur4GvLp5Jtzpgw7KV6hwCRq+7fc9fEkwtIHnjSmXuf4KpqmmHn20rgGBXOlfK\n"\
"dzxXqRNSOzc0PEv/vQveuTcQWaGYHtbcn1qnd5z1YaF2g9Wwtl2n\n"\
"-----END RSA PRIVATE KEY-----"


/* The constants above are set to const char * pointers defined in aws_dev_mode_key_provisioning.c,
 * and externed here for use in C files.  NOTE!  THIS IS DONE FOR CONVENIENCE
 * DURING AN EVALUATION PHASE AND IS NOT GOOD PRACTICE FOR PRODUCTION SYSTEMS 
 * WHICH MUST STORE KEYS SECURELY. */
extern const char clientcredentialCLIENT_CERTIFICATE_PEM[];
extern const char* clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM;
extern const char clientcredentialCLIENT_PRIVATE_KEY_PEM[];
extern const uint32_t clientcredentialCLIENT_CERTIFICATE_LENGTH;
extern const uint32_t clientcredentialCLIENT_PRIVATE_KEY_LENGTH;

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */

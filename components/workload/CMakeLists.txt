idf_component_register(SRCS "./client/request.c"
                            "./client/response_callback.c"
                            "./common/common.c"
                            "./common/coap_common.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES "openthread" "utilities")

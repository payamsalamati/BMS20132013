target_sources(${current_target} PUBLIC
icdaCAN_config.c
icdaCAN_followUpReceive.c
icdaCAN_prepareSend.c
icdaCAN_receive.c
icdaCAN_send.c
icdaCAN.c
)

target_include_directories(${current_target} PUBLIC "./")

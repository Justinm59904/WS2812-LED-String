add_executable(LEDString)

pico_generate_pio_header(LEDString ${CMAKE_CURRENT_LIST_DIR}/LEDString.pio)

target_sources(LEDString PRIVATE LEDString.c)

target_link_libraries(LEDString PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(LEDString)

example_auto_set_url(LEDString)
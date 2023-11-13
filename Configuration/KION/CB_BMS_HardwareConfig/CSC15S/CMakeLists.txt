target_sources(${current_target} PUBLIC
	AFE/afe_MC33771_config.c
)

target_include_directories(${current_target} PUBLIC
	"./"
	AFE
)

add_compile_definitions(CSC15S)

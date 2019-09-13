add_executable(setupper WIN32 setupper setupper_res.rc)
target_link_libraries(setupper PRIVATE ole32 shell32 uuid shlwapi)
target_compile_definitions(setupper PRIVATE -DUNICODE -D_UNICODE)

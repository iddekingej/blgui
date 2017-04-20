enable_testing()

message(STATUS "Testing enabled")
set(test_SRCS   test/lib/testclass.cpp
		test/lib/runner.cpp
		test/lib/testconfig.cpp
		test/base/test01.cpp
		test/base/run_base.cpp
		test/data/test_btrfs.cpp
		test/data/test_device.cpp
		test/data/test_devicelist.cpp
		test/data/test_mtab.cpp
		test/data/run_data.cpp
		test/data/test_deviceinfo.cpp
)

add_executable(blgui_test test/test.cpp ${test_SRCS} ${blgui_SRCS})

target_link_libraries(blgui_test
    ${blgui_LIBS}
    ${LIB_BLKID}    
    ${LIB_UDEV}
)


install(TARGETS blgui_test  ${INSTALL_TARGETS_DEFAULT_ARGS})
add_subdirectory(test)

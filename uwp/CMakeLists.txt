cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(AssetDeploy)

# Setup UWP platform
set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0.19041.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# todo: automatically apply based on msvc config if possible, libs work but DLL's have issues
set (BUILD_CONFIG "Debug")

# Define project
project(descent3-uwp LANGUAGES CXX)
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ${PROJECT_NAME})

# Config for main recomp build
set(D3_DIR CACHE PATH "")
if(NOT D3_DIR)
	message(FATAL_ERROR "D3_DIR must point to the Descent3 build folder")
endif()

add_executable(${PROJECT_NAME} WIN32
	main.cpp
)

set(BinDeps
	${D3_DIR}/_deps/uwplibs-src/x64/bin/dxil.dll
	${D3_DIR}/_deps/uwplibs-src/x64/bin/libgallium_wgl.dll
	${D3_DIR}/_deps/uwplibs-src/x64/bin/libuwp.dll
	${D3_DIR}/_deps/uwplibs-src/x64/bin/opengl32.dll
	${D3_DIR}/_deps/uwplibs-src/x64/bin/SDL3.dll
	${D3_DIR}/_deps/uwplibs-src/x64/bin/z-1.dll

	# todo: need a config that doesnt complain about missing files in other configs
	${D3_DIR}/build/${BUILD_CONFIG}/Descent3.dll

	Package.appxmanifest
)
source_group("BinDeps" FILES ${BinDeps})
set_source_files_properties(${BinDeps} PROPERTIES
	VS_COPY_TO_OUT_DIR Always
	VS_DEPLOYMENT_CONTENT TRUE
	VS_DEPLOYMENT_LOCATION "."
)

set(PkgAssets
	Assets/LockScreenLogo.scale-200.png
	Assets/Square44x44Logo.targetsize-24_altform-unplated.png
	Assets/Square44x44Logo.scale-200.png
	Assets/Square150x150Logo.scale-200.png
	Assets/StoreLogo.png
)
source_group("PkgAssets" FILES ${PkgAssets})
set_source_files_properties(${PkgAssets} PROPERTIES
	#VS_COPY_TO_OUT_DIR Always
	VS_DEPLOYMENT_CONTENT TRUE
	VS_DEPLOYMENT_LOCATION "Assets"
)

target_sources(${PROJECT_NAME} PRIVATE
	${BinDeps}
	${PkgAssets}
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${D3_DIR}/_deps/uwplibs-src/x64/include
)

set(BinLibs
	${D3_DIR}/Descent3/$<CONFIG>/Descent3.lib


	${D3_DIR}/_deps/uwplibs-src/x64/lib/libuwp.lib
	${D3_DIR}/_deps/uwplibs-src/x64/lib/SDL3.lib

	WindowsApp.lib
	OneCore.lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${BinLibs})

# Data deployment
set(DEPLOY_ROOT "${D3_DIR}/build/${BUILD_CONFIG}")
uwp_pkg(${PROJECT_NAME} ${DEPLOY_ROOT}/netgames "netgames")
uwp_pkg(${PROJECT_NAME} ${DEPLOY_ROOT}/online "online")

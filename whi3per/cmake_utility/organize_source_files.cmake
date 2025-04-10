file(GLOB source_files src/*.cc)
file(GLOB public_header_files include/public/whi3per/*.hh)
file(GLOB private_header_files include/private/whi3per/*.hh)

source_group("Source Files" FILES ${source_files})
source_group("Public Headers" FILES ${public_headers_files})
source_group("Private Headers" FILES ${private_headers_files}) 

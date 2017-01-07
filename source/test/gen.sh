rm -f *.pb.*
protoc -I=./ --cpp_out=./ *.proto

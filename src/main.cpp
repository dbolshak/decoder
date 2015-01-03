#include <stdio.h>
#include <stdlib.h>

#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf::io;

int main(int argc, const char** argv)
{
    FILE* fd = fopen(argv[1], "rb");

    FileInputStream* fileInputStream = new FileInputStream(fileno(fd), -1);
    GzipInputStream* gzipInputStream = new GzipInputStream(fileInputStream);

    delete gzipInputStream;
    delete fileInputStream;
    fclose(fd);

    return 0;
}


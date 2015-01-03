#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf::io;
using namespace std;

int main(int argc, const char** argv)
{
    FILE* fd = fopen(argv[1], "rb");

    FileInputStream* fileInputStream = new FileInputStream(fileno(fd), -1);
    GzipInputStream* gzipInputStream = new GzipInputStream(fileInputStream);

    string outputName = argv[1];
    outputName += ".out";
    ofstream out(outputName.c_str(), ios::out | ios::app | ios::binary);
    int size = 2048;
    const void* buffer = malloc(size);
    while (gzipInputStream->Next(&buffer, &size)) {
      out.write((const char*)buffer, size);
    }

    cout << gzipInputStream->ZlibErrorMessage();
    delete gzipInputStream;
    delete fileInputStream;
    fclose(fd);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/gzip_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace google::protobuf::io;
using namespace std;

int main(int argc, const char** argv)
{
    int fd = fileno(fopen(argv[1], "rb"));
    ZeroCopyInputStream* raw_input = new FileInputStream(fd);
    CodedInputStream* coded_input = new CodedInputStream(raw_input);

    google::protobuf::uint32  magic_number = 0;
    coded_input->ReadLittleEndian32(&magic_number);
    cout << "magic number:" << magic_number << endl;

    google::protobuf::uint32 size;
    coded_input->ReadVarint32(&size);

    char* text = new char[size + 1];
    coded_input->ReadRaw(text, size);
    text[size] = '\0';

    string outputName = argv[1];
    outputName += ".out";
    ofstream out(outputName.c_str(), ios::out | ios::app | ios::binary);

    out << text;
    delete coded_input;
    delete raw_input;
    close(fd);

    cout << "Text is: " << text << endl;
    delete [] text;

    return 0;
}


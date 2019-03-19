CXX?=clang++

compression_fuzz:
	$(CXX) -g -O3 -fsanitize=fuzzer compression_fuzzer.cpp lzo1x_compress.cpp lzo1x_decompress_safe.cpp -o compression_fuzz
	./compression_fuzz

decompression_fuzz:
	$(CXX) -g -O3 -fsanitize=fuzzer decompression_fuzzer.cpp lzo1x_compress.cpp lzo1x_decompress_safe.cpp -o compression_fuzz
	./decompression_fuzz

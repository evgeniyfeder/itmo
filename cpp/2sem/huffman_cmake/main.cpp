#include <iostream>
#include <fstream>
#include <cstring>
#include "huffman_cod.h"

void write(const bits_sequence &bs, std::ofstream &out) {
	uint32_t size = bs.size();
	out.write((char *)&size, sizeof(uint32_t));
	size_t ost = bs.size() % bits_sequence::sizeof_type;
	if (ost != 0)
		out.write((char *)bs.data().data(), (bs.size() / bits_sequence::sizeof_type + 1) * sizeof(uint64_t));
	else
		out.write((char *)bs.data().data(), bs.size() / bits_sequence::sizeof_type * sizeof(uint64_t));
}

size_t get_bytes_size(size_t size_bits) { return size_bits / bits_sequence::sizeof_type + ((size_bits % bits_sequence::sizeof_type) != 0); }

#define MAX_BLOCK 128000

int main(int argc, char *argv[]) {
    try {

        if (argc != 4)
            throw std::runtime_error("Not 4 arguments");

        // std::string file = "Huffman";
        // argv[1] = (char *) "enc", argv[2] = (char *) (file + ".jpg").c_str(), argv[3] = (char *) (file + ".out").c_str();
        // argv[1] = (char *) "dec", argv[2] = (char *) (file + ".out").c_str(), argv[3] = (char *) (file + ".dec").c_str();

        std::ifstream in(argv[2], std::ios::in | std::ios::binary);
        std::ofstream out(argv[3], std::ios::out | std::ios::binary);

        if (!in || !out)
            throw std::runtime_error("Bad input or output files");

        // enc chehov.txt chechov.out
        if (strcmp(argv[1], "enc") == 0) {
            frequency_counter fc;
            std::vector<uint8_t> block(MAX_BLOCK);

            while (in) {
                memset(block.data(), 0, block.size());
                in.read((char *) block.data(), block.size());
                fc.add_file_block(block.data(), (size_t) in.gcount());
            }

            in.clear();
            in.seekg(0);

            huffman_encoder he(fc);

            bits_sequence bs;
            std::vector<uint8_t> alpha;
            he.get_tree_code(bs, alpha);

            uint32_t alpha_size = alpha.size();
            out.write((char *) &alpha_size, sizeof(uint32_t));
            write(bs, out);
            out.write((char *) alpha.data(), alpha.size());

            while (in) {
                in.read((char *) block.data(), block.size());
                write(he.code_part(block.data(), (size_t) in.gcount()), out);
            }
        } else if (strcmp(argv[1], "dec") == 0) {
            uint32_t size_tree, size_alpha;

            if (in.read((char *) &size_alpha, sizeof(uint32_t)).gcount() == 0)
                throw std::runtime_error("Bad fil format");
            if (in.read((char *) &size_tree, sizeof(uint32_t)).gcount() == 0)
                throw std::runtime_error("Bad fil format");;

            uint32_t size_mem = get_bytes_size(size_tree);

            if (size_tree > 1000 || size_alpha > 300)
                throw std::runtime_error("Bad file format");

            std::vector<uint8_t> mem_char(size_mem * sizeof(uint64_t) + size_alpha);
            if ((size_t) in.read((char *) mem_char.data(), mem_char.size()).gcount() != mem_char.size())
                throw std::runtime_error("Bad fil format");

            huffman_decoder hd(mem_char.data(), size_tree, size_alpha);

            while (in) {
                uint32_t size_bytes = 0, size_bits = 0;
                if (in.read((char *) &size_bits, sizeof(uint32_t)).gcount() == 0)
                    break;

                size_bytes = get_bytes_size(size_bits);

                std::vector<uint64_t> mem_i64(size_bytes);
                if ((size_t) in.read((char *) mem_i64.data(), mem_i64.size() * sizeof(uint64_t)).gcount() !=
                    mem_i64.size() * sizeof(uint64_t))
                    throw std::runtime_error("Bad fil format");

                bits_sequence bs(mem_i64);
                if (size_bits % bits_sequence::sizeof_type != 0)
                    bs.remove_last(bits_sequence::sizeof_type - (size_bits % bits_sequence::sizeof_type));
                std::vector<uint8_t> res = hd.decode_part(bs);
                out.write((char *) res.data(), res.size());
            }
        } else {
            throw std::runtime_error("Bad 2 argument(need dec or enc)");
        }
    } catch(std::runtime_error &ex) {
        std::cout << "Bad file format or programm arguments";
    }
}
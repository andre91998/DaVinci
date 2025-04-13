#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <string>

class Encrypter {
    public:
        virtual ~Encrypter() = default;
        
        static std::string encrypt(const std::string& src) {
            
            std::string encryptedSrc = src;
            //encrypt char by char
            for (int i=0 ; i < src.size(); i++){

                encryptedSrc.at(i) = src.at(i) + encryptionKey;
        
                std::cout << " o\t\t\tEncrypting Character " << src << " ---> " << encryptedSrc << "\t\t\t\t    o" << std::endl; 
            }

            return escape_sql_string(encryptedSrc);
        }

        static std::string decrypt(const std::string& encryptedSrc) {
            std::string decryptedSrc = encryptedSrc;
            decryptedSrc.erase(std::remove(decryptedSrc.begin(), decryptedSrc.end(), '\\'), decryptedSrc.end());
            //decrypt char by char
            for (int i=0 ; i < decryptedSrc.size(); i++){

                decryptedSrc.at(i) = decryptedSrc.at(i) - encryptionKey;
        
                std::cout << " o\t\t\tDecrypting Character " << encryptedSrc << " ---> " << decryptedSrc << "\t\t\t\t    o" << std::endl;
            }

            return decryptedSrc;
        }

        static std::string escape_sql_string(const std::string& input) {
            std::unordered_map<char, std::string> escape_map = {
                {'\'', "''"},
                {'\"', "\\\""},
                {'\\', "\\\\"},
                {'\0', "\\0"},
                {'\n', "\\n"},
                {'\r', "\\r"},
                {'\x1a', "\\Z"},
                {';', "\\;"},
                {'%', "\\%"},
                {'_', "\\_"},
                {'\b', "\\b"},
                {'\t', "\\t"}
            };
        
            std::ostringstream escaped;
            escaped << "'";
        
            for (char c : input) {
                if (escape_map.find(c) != escape_map.end()) {
                    escaped << escape_map[c];
                } else {
                    escaped << c;
                }
            }
        
            escaped << "'";
            return escaped.str();
        }

    private:
        const static int encryptionKey = 5;
    };

#endif // ENCRYPTER_H
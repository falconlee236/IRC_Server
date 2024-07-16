#include "../includes/Message.hpp"

// Message::Message(void){

// }
Message::~Message(){}
// Message::Message(const Message& obj){

// }
// Message& Message::operator= (const Message& obj){

// }

/*
Tue Jul 16 2024 13:28:37 USERINPUT: C[811AAAAAI] I CAP LS 302
Tue Jul 16 2024 13:28:37 USERINPUT: C[811AAAAAI] I JOIN :
67 C
65 A
80 P
32 ' '
76 L
83 S
32 ' '
51 3
48 0
50 2
13 CR (\r)
10 LF (\n)
74 J
79 O
73 I
78 N
32 ' '
58 ':'
13 \r
10 \n
그다음 대기
Tue Jul 16 2024 13:28:37 USEROUTPUT: C[811AAAAAI] O :irc.local 451 * JOIN :You have not registered.
Tue Jul 16 2024 13:28:37 USERINPUT: C[811AAAAAI] I PASS 123
Tue Jul 16 2024 13:28:37 USERINPUT: C[811AAAAAI] I NICK sang
Tue Jul 16 2024 13:28:37 USERINPUT: C[811AAAAAI] I USER root root 127.0.0.1 :root
Tue Jul 16 2024 13:28:42 USEROUTPUT: C[811AAAAAI] O :irc.local NOTICE sang :*** Could not resolve your hostname: Request timed out; using your IP address (127.0.0.1) instead.
*/

std::vector<std::string> Message::splitN(const std::string& str, char delimiter, size_t n) {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string token;
    size_t count = 0;

    while (std::getline(stream, token, delimiter) && count < n - 1) {
        tokens.push_back(token);
        count++;
    }
    // Add the remaining part of the string
    if (stream) {
        std::string remaining((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        if (!token.empty())
            remaining = token + delimiter + remaining;
        tokens.push_back(remaining);
    }
    return tokens;
}


Message::Message(std::string str){
	std::vector<std::string> ans = splitN(str, ' ', 2);
	for(size_t i = 0; i < ans.size(); i++) 
		std::cout << ans[i] << "\n";
	std::cout << ans.size() << "\n";
}
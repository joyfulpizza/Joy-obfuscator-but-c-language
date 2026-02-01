#include <iostream>
#include <string>

std::string xorEnc(const std::string& s, unsigned char k) {
    std::string o = s;
    for (char& c : o) c ^= k;
    return o;
}

std::string toLuaEscaped(const std::string& s) {
    std::string o;
    for (unsigned char c : s)
        o += "\\" + std::to_string((int)c);
    return o;
}

int main() {
    unsigned char KEY = 0x5C;

    std::string bytecode =
        "9||;"
        "1|Hello from VM|;"
        "2|print|;"
        "3||;";

    std::string enc = xorEnc(bytecode, KEY);
    std::string blob = toLuaEscaped(enc);

    std::cout <<
"local B=\"" << blob << "\"\n"
"local function F(b)\n"
" local x=0\n"
" for i=1,#b do x=(x+string.byte(b,i))%255 end\n"
" return x>127\n"
"end\n"
"local function D(s)\n"
" local o=\"\"\n"
" for i=1,#s do o=o..string.char(string.byte(s,i)~" << (int)KEY << ") end\n"
" return o\n"
"end\n"
"local function V()\n"
" local P={}\n"
" for ins in string.gmatch(D(B),\"([^;]+);\") do\n"
"  local a,b=ins:match(\"([^|]+)|([^|]*)|\")\n"
"  P[#P+1]={tonumber(a),b}\n"
" end\n"
" local S={}\n"
" local pc=1\n"
" while true do\n"
"  local i=P[pc]\n"
"  if not i then break end\n"
"  if i[1]==1 then\n"
"   S[#S+1]=i[2]\n"
"  elseif i[1]==2 then\n"
"   _G[i[2]](S[#S])\n"
"  elseif i[1]==9 then\n"
"   local _=(pc*7)%3\n"
"  elseif i[1]==3 then\n"
"   return\n"
"  end\n"
"  pc=pc+1\n"
" end\n"
"end\n"
"if F(B) then for i=1,3 do math.random() end end\n"
"V()\n";

    return 0;
}

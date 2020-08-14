/*
# MIT License
# Copyright(c) 2020 NovusCore
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files(the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions :
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
*/
#pragma once
#include "../NovusTypes.h"
#include <vector>
#include <robin_hood.h>
#include <shared_mutex>

class Bytebuffer;

class StringTable
{
public:
    // Add string, return index into table
    u32 AddString(const std::string& string);

    const std::string& GetString(u32 index);
    u32 GetStringHash(u32 index);

    size_t GetNumStrings() { return _strings.size(); }

    void Serialize(Bytebuffer* bytebuffer);
    void Deserialize(Bytebuffer* bytebuffer);

    void CopyFrom(StringTable& other);

private:
    bool TryFindHashedString(u32 hash, u32& index);

private:
    std::vector<std::string> _strings;
    std::vector<u32> _hashes;

    std::shared_mutex _mutex;
};
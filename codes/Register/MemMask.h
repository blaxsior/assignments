#pragma once

enum class MemoryMask {
    CLEAR = 0b00000000, // 0
    OPCODE = 0b11000000, // 위부터 2자리
    OPERAND = 0b00111111, // 아래부터 6자리
};
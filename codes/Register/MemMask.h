#pragma once

enum class MemoryMask {
    CLEAR = 0b00000000, // 0
    OPCODE = 0b11000000, // ������ 2�ڸ�
    OPERAND = 0b00111111, // �Ʒ����� 6�ڸ�
};
package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNull;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

public class LRUCacheTest {
    @Test
    public void testCase1() {
        var lru = new LRUCache<Integer, Integer>(3);
        assertNull(lru.getValue(0));
        lru.put(1, 1);
        assertEquals(lru.getValue(0), Integer.valueOf(1));

        lru.put(2, 2);
        assertEquals(lru.getValue(0), Integer.valueOf(2));
        assertEquals(lru.getValue(1), Integer.valueOf(1));
        assertNull(lru.getValue(2));

        lru.put(3, 3);
        assertEquals(lru.getValue(0), Integer.valueOf(3));
        assertEquals(lru.getValue(1), Integer.valueOf(2));
        assertEquals(lru.getValue(2), Integer.valueOf(1));
        assertNull(lru.getValue(3));

        lru.put(1, 1);
        assertEquals(lru.getValue(0), Integer.valueOf(1));
        assertEquals(lru.getValue(1), Integer.valueOf(3));
        assertEquals(lru.getValue(2), Integer.valueOf(2));
        assertNull(lru.getValue(3));

        lru.put(4, 4);
        assertEquals(lru.getValue(0), Integer.valueOf(4));
        assertEquals(lru.getValue(1), Integer.valueOf(1));
        assertEquals(lru.getValue(2), Integer.valueOf(3));
        assertFalse(lru.contains(2));
        assertNull(lru.getValue(3));

        lru.put(2, 2);
        assertEquals(lru.getValue(0), Integer.valueOf(2));
        assertEquals(lru.getValue(1), Integer.valueOf(4));
        assertEquals(lru.getValue(2), Integer.valueOf(1));
        assertFalse(lru.contains(3));
        assertNull(lru.getValue(3));

        assertEquals(lru.get(1), Integer.valueOf(1));
        assertEquals(lru.getValue(0), Integer.valueOf(1));
        assertEquals(lru.getValue(1), Integer.valueOf(2));
        assertEquals(lru.getValue(2), Integer.valueOf(4));
        assertNull(lru.getValue(3));

        assertEquals(lru.get(4), Integer.valueOf(4));
        assertEquals(lru.getValue(0), Integer.valueOf(4));
        assertEquals(lru.getValue(1), Integer.valueOf(1));
        assertEquals(lru.getValue(2), Integer.valueOf(2));
        assertNull(lru.getValue(3));
    }

    @Test
    public void testCase2() {
        var lru = new LRUCache<Integer, Integer>(105);
        lru.put(33, 219);
        assertNull(lru.get(39));
        lru.put(96, 56);
        assertNull(lru.get(129));
        assertNull(lru.get(115));
        assertNull(lru.get(112));
        lru.put(3, 280);
        assertNull(lru.get(40));
        lru.put(85, 193);
        lru.put(10, 10);
        lru.put(100, 136);
        lru.put(12, 66);
        lru.put(81, 261);
        lru.put(33, 58);
        assertEquals(lru.get(3), Integer.valueOf(280));
        lru.put(121, 308);
        lru.put(129, 263);
        assertNull(lru.get(105));
        lru.put(104, 38);
        lru.put(65, 85);
        lru.put(3, 141);
        lru.put(29, 30);
        lru.put(80, 191);
        lru.put(52, 191);
        lru.put(8, 300);
        assertNull(lru.get(136));
        lru.put(48, 261);
        lru.put(3, 193);
        lru.put(133, 193);
        lru.put(60, 183);
        lru.put(128, 148);
        lru.put(52, 176);
        assertEquals(lru.get(48), Integer.valueOf(261));
        lru.put(48, 119);
        lru.put(10, 241);
        assertNull(lru.get(124));
        lru.put(130, 127);
        assertNull(lru.get(61));
        lru.put(124, 27);
        assertNull(lru.get(94));
        lru.put(29, 304);
        lru.put(102, 314);
        assertNull(lru.get(110));
        lru.put(23, 49);
        lru.put(134, 12);
        lru.put(55, 90);
        assertNull(lru.get(14));
        assertEquals(lru.get(104), Integer.valueOf(38));
        lru.put(77, 165);
        lru.put(60, 160);
        assertNull(lru.get(117));
        lru.put(58, 30);
        assertNull(lru.get(54));
        assertNull(lru.get(136));
        assertEquals(lru.get(128), Integer.valueOf(148));
        assertNull(lru.get(131));
        lru.put(48, 114);
        assertNull(lru.get(136));
        lru.put(46, 51);
        lru.put(129, 291);
        lru.put(96, 207);
        assertNull(lru.get(131));
        lru.put(89, 153);
        lru.put(120, 154);
        assertNull(lru.get(111));
        assertNull(lru.get(47));
        assertNull(lru.get(5));
        lru.put(114, 157);
        lru.put(57, 82);
        lru.put(113, 106);
        lru.put(74, 208);
        assertNull(lru.get(56));
        assertNull(lru.get(59));
        assertEquals(lru.get(100), Integer.valueOf(136));
        assertNull(lru.get(132));
        lru.put(127, 202);
        assertNull(lru.get(75));
        lru.put(102, 147);
        assertNull(lru.get(37));
        lru.put(53, 79);
        lru.put(119, 220);
        assertNull(lru.get(47));
        assertNull(lru.get(101));
        assertEquals(lru.get(89), Integer.valueOf(153));
        assertNull(lru.get(20));
        assertNull(lru.get(93));
        assertNull(lru.get(7));
        lru.put(48, 109);
        lru.put(71, 146);
        assertNull(lru.get(43));
        assertNull(lru.get(122));
        lru.put(3, 160);
        assertNull(lru.get(17));
        lru.put(80, 22);
        lru.put(80, 272);
        assertNull(lru.get(75));
        assertNull(lru.get(117));
        lru.put(76, 204);
        lru.put(74, 141);
        lru.put(107, 93);
        lru.put(34, 280);
        lru.put(31, 94);
        assertNull(lru.get(132));
        lru.put(71, 258);
        assertNull(lru.get(61));
        assertEquals(lru.get(60), Integer.valueOf(160));
        lru.put(69, 272);
        assertEquals(lru.get(46), Integer.valueOf(51));
        lru.put(42, 264);
        lru.put(87, 126);
        lru.put(107, 236);
        lru.put(131, 218);
        assertNull(lru.get(79));
        lru.put(41, 71);
        lru.put(94, 111);
        lru.put(19, 124);
        lru.put(52, 70);
        assertEquals(lru.get(131), Integer.valueOf(218));
        assertNull(lru.get(103));
        assertEquals(lru.get(81), Integer.valueOf(261));
        assertNull(lru.get(126));
        lru.put(61, 279);
        lru.put(37, 100);
        assertNull(lru.get(95));
        assertNull(lru.get(54));
        lru.put(59, 136);
        lru.put(101, 219);
        lru.put(15, 248);
        lru.put(37, 91);
        lru.put(11, 174);
        lru.put(99, 65);
        lru.put(105, 249);
        assertEquals(lru.get(85), Integer.valueOf(193));
        lru.put(108, 287);
        lru.put(96, 4);
        assertNull(lru.get(70));
        assertNull(lru.get(24));
        lru.put(52, 206);
        lru.put(59, 306);
        lru.put(18, 296);
        lru.put(79, 95);
        lru.put(50, 131);
        lru.put(3, 161);
        lru.put(2, 229);
        lru.put(39, 183);
        lru.put(90, 225);
        lru.put(75, 23);
        lru.put(136, 280);
        assertEquals(lru.get(119), Integer.valueOf(220));
        lru.put(81, 272);
        assertNull(lru.get(106));
        assertNull(lru.get(106));
        assertNull(lru.get(70));
        lru.put(73, 60);
        lru.put(19, 250);
        lru.put(82, 291);
        lru.put(117, 53);
        lru.put(16, 176);
        assertNull(lru.get(40));
        lru.put(7, 70);
        lru.put(135, 212);
        assertEquals(lru.get(59), Integer.valueOf(306));
        lru.put(81, 201);
        lru.put(75, 305);
        assertEquals(lru.get(101), Integer.valueOf(219));
        lru.put(8, 250);
        assertNull(lru.get(38));
        lru.put(28, 220);
        assertNull(lru.get(21));
        lru.put(105, 266);
        assertEquals(lru.get(105), Integer.valueOf(266));
        assertEquals(lru.get(85), Integer.valueOf(193));
        assertEquals(lru.get(55), Integer.valueOf(90));
        assertNull(lru.get(6));
        lru.put(78, 83);
        assertNull(lru.get(126));
        assertEquals(lru.get(102), Integer.valueOf(147));
        assertNull(lru.get(66));
        lru.put(61, 42);
        lru.put(127, 35);
        lru.put(117, 105);
        assertEquals(lru.get(128), Integer.valueOf(148));
        assertEquals(lru.get(102), Integer.valueOf(147));
        assertEquals(lru.get(50), Integer.valueOf(131));
        lru.put(24, 133);
        lru.put(40, 178);
        lru.put(78, 157);
        lru.put(71, 22);
        assertNull(lru.get(25));
        assertEquals(lru.get(82), Integer.valueOf(291));
        assertEquals(lru.get(129), Integer.valueOf(291));
        lru.put(126, 12);
        assertNull(lru.get(45));
        assertEquals(lru.get(40), Integer.valueOf(178));
        assertNull(lru.get(86));
        assertEquals(lru.get(100), Integer.valueOf(136));
        lru.put(30, 110);
        assertNull(lru.get(49));
        lru.put(47, 185);
        lru.put(123, 101);
        assertEquals(lru.get(102), Integer.valueOf(147));
        assertNull(lru.get(5));
        lru.put(40, 267);
        lru.put(48, 155);
        assertEquals(lru.get(108), Integer.valueOf(287));
        assertNull(lru.get(45));
        lru.put(14, 182);
        lru.put(20, 117);
        lru.put(43, 124);
        assertNull(lru.get(38));
        lru.put(77, 158);
        assertNull(lru.get(111));
        assertEquals(lru.get(39), Integer.valueOf(183));
        lru.put(69, 126);
        lru.put(113, 199);
        lru.put(21, 216);
        assertEquals(lru.get(11), Integer.valueOf(174));
        lru.put(117, 207);
        assertEquals(lru.get(30), Integer.valueOf(110));
        lru.put(97, 84);
        assertNull(lru.get(109));
        lru.put(99, 218);
        assertNull(lru.get(109));
        lru.put(113, 1);
        assertNull(lru.get(62));
        lru.put(49, 89);
        lru.put(53, 311);
        assertEquals(lru.get(126), Integer.valueOf(12));
        lru.put(32, 153);
        lru.put(14, 296);
        assertNull(lru.get(22));
        lru.put(14, 225);
        assertEquals(lru.get(49), Integer.valueOf(89));
        assertEquals(lru.get(75), Integer.valueOf(305));
        lru.put(61, 241);
        assertEquals(lru.get(7), Integer.valueOf(70));
        assertNull(lru.get(6));
        assertEquals(lru.get(31), Integer.valueOf(94));
        lru.put(75, 15);
        assertNull(lru.get(115));
        lru.put(84, 181);
        lru.put(125, 111);
        lru.put(105, 94);
        lru.put(48, 294);
        assertNull(lru.get(106));
        assertEquals(lru.get(61), Integer.valueOf(241));
        lru.put(53, 190);
        assertEquals(lru.get(16), Integer.valueOf(176));
        lru.put(12, 252);
        assertEquals(lru.get(28), Integer.valueOf(220));
        lru.put(111, 122);
        assertNull(lru.get(122));
        lru.put(10, 21);
        assertEquals(lru.get(59), Integer.valueOf(306));
        assertNull(lru.get(72));
        assertEquals(lru.get(39), Integer.valueOf(183));
        assertNull(lru.get(6));
        assertEquals(lru.get(126), Integer.valueOf(12));
        lru.put(131, 177);
        lru.put(105, 253);
        assertNull(lru.get(26));
        lru.put(43, 311);
        assertEquals(lru.get(79), Integer.valueOf(95));
        lru.put(91, 32);
        lru.put(7, 141);
        assertNull(lru.get(38));
        assertNull(lru.get(13));
        lru.put(79, 135);
        assertEquals(lru.get(43), Integer.valueOf(311));
        assertEquals(lru.get(94), Integer.valueOf(111));
        lru.put(80, 182);
        assertEquals(lru.get(53), Integer.valueOf(190));
        lru.put(120, 309);
        lru.put(3, 109);
        assertEquals(lru.get(97), Integer.valueOf(84));
        lru.put(9, 128);
        lru.put(114, 121);
        assertNull(lru.get(56));
        assertNull(lru.get(56));
        lru.put(124, 86);
        lru.put(34, 145);
        assertEquals(lru.get(131), Integer.valueOf(177));
        assertEquals(lru.get(78), Integer.valueOf(157));
        lru.put(86, 21);
        assertNull(lru.get(98));
        lru.put(115, 164);
        lru.put(47, 225);
        assertNull(lru.get(95));
        lru.put(89, 55);
        lru.put(26, 134);
        lru.put(8, 15);
        assertEquals(lru.get(11), Integer.valueOf(174));
        lru.put(84, 276);
        lru.put(81, 67);
        assertEquals(lru.get(46), Integer.valueOf(51));
        assertEquals(lru.get(39), Integer.valueOf(183));
        assertNull(lru.get(92));
        assertEquals(lru.get(96), Integer.valueOf(4));
        lru.put(89, 51);
        lru.put(136, 240);
        assertNull(lru.get(45));
        assertNull(lru.get(27));
        lru.put(24, 209);
        lru.put(82, 145);
        assertEquals(lru.get(10), Integer.valueOf(21));
        lru.put(104, 225);
        lru.put(120, 203);
        lru.put(121, 108);
        lru.put(11, 47);
        assertEquals(lru.get(89), Integer.valueOf(51));
        lru.put(80, 66);
        assertEquals(lru.get(16), Integer.valueOf(176));
        lru.put(95, 101);
        assertEquals(lru.get(49), Integer.valueOf(89));
        assertNull(lru.get(1));
        lru.put(77, 184);
        assertNull(lru.get(27));
        lru.put(74, 313);
        lru.put(14, 118);
        assertEquals(lru.get(16), Integer.valueOf(176));
        assertEquals(lru.get(74), Integer.valueOf(313));
        lru.put(88, 251);
        assertEquals(lru.get(124), Integer.valueOf(86));
        lru.put(58, 101);
        lru.put(42, 81);
        assertEquals(lru.get(2), Integer.valueOf(229));
        lru.put(133, 101);
        assertEquals(lru.get(16), Integer.valueOf(176));
        lru.put(1, 254);
        lru.put(25, 167);
        lru.put(53, 56);
        lru.put(73, 198);
        assertEquals(lru.get(48), Integer.valueOf(294));
        assertEquals(lru.get(30), Integer.valueOf(110));
        assertEquals(lru.get(95), Integer.valueOf(101));
        lru.put(90, 102);
        lru.put(92, 56);
        lru.put(2, 130);
        lru.put(52, 11);
        assertEquals(lru.get(9), Integer.valueOf(128));
        assertEquals(lru.get(23), Integer.valueOf(49));
        lru.put(53, 275);
        lru.put(23, 258);
        assertEquals(lru.get(57), Integer.valueOf(82));
        lru.put(136, 183);
        lru.put(75, 265);
        assertEquals(lru.get(85), Integer.valueOf(193));
        lru.put(68, 274);
        lru.put(15, 255);
        assertEquals(lru.get(85), Integer.valueOf(193));
        lru.put(33, 314);
        lru.put(101, 223);
        lru.put(39, 248);
        lru.put(18, 261);
        lru.put(37, 160);
        assertNull(lru.get(112));
        assertEquals(lru.get(65), Integer.valueOf(85));
        lru.put(31, 240);
        lru.put(40, 295);
        lru.put(99, 231);
        assertEquals(lru.get(123), Integer.valueOf(101));
        lru.put(34, 43);
        assertEquals(lru.get(87), Integer.valueOf(126));
        assertEquals(lru.get(80), Integer.valueOf(66));
        lru.put(47, 279);
        lru.put(89, 299);
        assertNull(lru.get(72));
        lru.put(26, 277);
        lru.put(92, 13);
        lru.put(46, 92);
        lru.put(67, 163);
        lru.put(85, 184);
        assertNull(lru.get(38));
        lru.put(35, 65);
        assertNull(lru.get(70));
        assertEquals(lru.get(81), Integer.valueOf(67));
        lru.put(40, 65);
        assertEquals(lru.get(80), Integer.valueOf(66));
        lru.put(80, 23);
        lru.put(76, 258);
        assertEquals(lru.get(69), Integer.valueOf(126));
        assertEquals(lru.get(133), Integer.valueOf(101));
        lru.put(123, 196);
        lru.put(119, 212);
        lru.put(13, 150);
        lru.put(22, 52);
        lru.put(20, 105);
        lru.put(61, 233);
        assertEquals(lru.get(97), Integer.valueOf(84));
        lru.put(128, 307);
        assertEquals(lru.get(85), Integer.valueOf(184));
        assertEquals(lru.get(80), Integer.valueOf(23));
        assertEquals(lru.get(73), Integer.valueOf(198));
        assertEquals(lru.get(30), Integer.valueOf(110));
        lru.put(46, 44);
        assertEquals(lru.get(95), Integer.valueOf(101));
        lru.put(121, 211);
        lru.put(48, 307);
        assertEquals(lru.get(2), Integer.valueOf(130));
        lru.put(27, 166);
        assertEquals(lru.get(50), Integer.valueOf(131));
        lru.put(75, 41);
        lru.put(101, 105);
        assertEquals(lru.get(2), Integer.valueOf(130));
        lru.put(110, 121);
        lru.put(32, 88);
        lru.put(75, 84);
        lru.put(30, 165);
        lru.put(41, 142);
        lru.put(128, 102);
        lru.put(105, 90);
        lru.put(86, 68);
        lru.put(13, 292);
        lru.put(83, 63);
        lru.put(5, 239);
        assertEquals(lru.get(5), Integer.valueOf(239));
        lru.put(68, 204);
        assertEquals(lru.get(127), Integer.valueOf(35));
        lru.put(42, 137);
        assertNull(lru.get(93));
        lru.put(90, 258);
        lru.put(40, 275);
        lru.put(7, 96);
        assertEquals(lru.get(108), Integer.valueOf(287));
        lru.put(104, 91);
        assertNull(lru.get(63));
        assertEquals(lru.get(31), Integer.valueOf(240));
        lru.put(31, 89);
        assertEquals(lru.get(74), Integer.valueOf(313));
        assertEquals(lru.get(81), Integer.valueOf(67));
        lru.put(126, 148);
        assertNull(lru.get(107));
        lru.put(13, 28);
        lru.put(21, 139);
        assertEquals(lru.get(114), Integer.valueOf(121));
        assertEquals(lru.get(5), Integer.valueOf(239));
        assertEquals(lru.get(89), Integer.valueOf(299));
        assertEquals(lru.get(133), Integer.valueOf(101));
        assertEquals(lru.get(20), Integer.valueOf(105));
        lru.put(96, 135);
        lru.put(86, 100);
        lru.put(83, 75);
        assertEquals(lru.get(14), Integer.valueOf(118));
        lru.put(26, 195);
        assertEquals(lru.get(37), Integer.valueOf(160));
        lru.put(1, 287);
        assertEquals(lru.get(79), Integer.valueOf(135));
        assertEquals(lru.get(15), Integer.valueOf(255));
        assertNull(lru.get(6));
        lru.put(68, 11);
        assertEquals(lru.get(52), Integer.valueOf(11));
        lru.put(124, 80);
        lru.put(123, 277);
        lru.put(99, 281);
        assertEquals(lru.get(133), Integer.valueOf(101));
        assertEquals(lru.get(90), Integer.valueOf(258));
        assertNull(lru.get(45));
        assertEquals(lru.get(127), Integer.valueOf(35));
        lru.put(9, 68);
        lru.put(123, 6);
        lru.put(124, 251);
        lru.put(130, 191);
        lru.put(23, 174);
        lru.put(69, 295);
        assertEquals(lru.get(32), Integer.valueOf(88));
        assertEquals(lru.get(37), Integer.valueOf(160));
        lru.put(1, 64);
        lru.put(48, 116);
        assertEquals(lru.get(68), Integer.valueOf(11));
        lru.put(117, 173);
        lru.put(16, 89);
        assertEquals(lru.get(84), Integer.valueOf(276));
        lru.put(28, 234);
        assertEquals(lru.get(129), Integer.valueOf(291));
        assertEquals(lru.get(89), Integer.valueOf(299));
        assertEquals(lru.get(55), Integer.valueOf(90));
        assertEquals(lru.get(83), Integer.valueOf(75));
        lru.put(99, 264);
        assertEquals(lru.get(129), Integer.valueOf(291));
        assertEquals(lru.get(84), Integer.valueOf(276));
        assertEquals(lru.get(14), Integer.valueOf(118));
        lru.put(26, 274);
        assertNull(lru.get(109));
        assertEquals(lru.get(110), Integer.valueOf(121));
        lru.put(96, 120);
        lru.put(128, 207);
        assertEquals(lru.get(12), Integer.valueOf(252));
        lru.put(99, 233);
        lru.put(20, 305);
        lru.put(26, 24);
        lru.put(102, 32);
        assertEquals(lru.get(82), Integer.valueOf(145));
        lru.put(16, 30);
        lru.put(5, 244);
        assertEquals(lru.get(130), Integer.valueOf(191));
        lru.put(109, 36);
        lru.put(134, 162);
        lru.put(13, 165);
        lru.put(45, 235);
        lru.put(112, 80);
        assertNull(lru.get(6));
        lru.put(34, 98);
        lru.put(64, 250);
        lru.put(18, 237);
        lru.put(72, 21);
        lru.put(42, 105);
        lru.put(57, 108);
        lru.put(28, 229);
        assertEquals(lru.get(83), Integer.valueOf(75));
        lru.put(1, 34);
        lru.put(93, 151);
        lru.put(132, 94);
        lru.put(18, 24);
        lru.put(57, 68);
        lru.put(42, 137);
        assertEquals(lru.get(35), Integer.valueOf(65));
        assertEquals(lru.get(80), Integer.valueOf(23));
        lru.put(10, 288);
        assertEquals(lru.get(21), Integer.valueOf(139));
        assertEquals(lru.get(115), Integer.valueOf(164));
        assertEquals(lru.get(131), Integer.valueOf(177));
        assertEquals(lru.get(30), Integer.valueOf(165));
        assertEquals(lru.get(43), Integer.valueOf(311));
        lru.put(97, 262);
        lru.put(55, 146);
        lru.put(81, 112);
        lru.put(2, 212);
        lru.put(5, 312);
        lru.put(82, 107);
        lru.put(14, 151);
        assertEquals(lru.get(77), Integer.valueOf(184));
        lru.put(60, 42);
        lru.put(90, 309);
        assertEquals(lru.get(90), Integer.valueOf(309));
        lru.put(131, 220);
        assertEquals(lru.get(86), Integer.valueOf(100));
        lru.put(106, 85);
        lru.put(85, 254);
        assertEquals(lru.get(14), Integer.valueOf(151));
        lru.put(66, 262);
        lru.put(88, 243);
        assertNull(lru.get(3));
        lru.put(50, 301);
        lru.put(118, 91);
        assertEquals(lru.get(25), Integer.valueOf(167));
        assertEquals(lru.get(105), Integer.valueOf(90));
        assertNull(lru.get(100));
        assertEquals(lru.get(89), Integer.valueOf(299));
        lru.put(111, 152);
        lru.put(65, 24);
        lru.put(41, 264);
        assertEquals(lru.get(117), Integer.valueOf(173));
        assertEquals(lru.get(117), Integer.valueOf(173));
        lru.put(80, 45);
        assertNull(lru.get(38));
        lru.put(11, 151);
        lru.put(126, 203);
        lru.put(128, 59);
        lru.put(6, 129);
        assertNull(lru.get(91));
        lru.put(118, 2);
        lru.put(50, 164);
        assertEquals(lru.get(74), Integer.valueOf(313));
        assertEquals(lru.get(80), Integer.valueOf(45));
        lru.put(48, 308);
        lru.put(109, 82);
        lru.put(3, 48);
        lru.put(123, 10);
        lru.put(59, 249);
        lru.put(128, 64);
        lru.put(41, 287);
        lru.put(52, 278);
        lru.put(98, 151);
        assertEquals(lru.get(12), Integer.valueOf(252));
        assertEquals(lru.get(25), Integer.valueOf(167));
        lru.put(18, 254);
        lru.put(24, 40);
        assertEquals(lru.get(119), Integer.valueOf(212));
        lru.put(66, 44);
        lru.put(61, 19);
        lru.put(80, 132);
        lru.put(62, 111);
        assertEquals(lru.get(80), Integer.valueOf(132));
        lru.put(57, 188);
        assertEquals(lru.get(132), Integer.valueOf(94));
        assertEquals(lru.get(42), Integer.valueOf(137));
        lru.put(18, 314);
        assertEquals(lru.get(48), Integer.valueOf(308));
        lru.put(86, 138);
        assertNull(lru.get(8));
        lru.put(27, 88);
        lru.put(96, 178);
        lru.put(17, 104);
        lru.put(112, 86);
        assertEquals(lru.get(25), Integer.valueOf(167));
        lru.put(129, 119);
        lru.put(93, 44);
        assertEquals(lru.get(115), Integer.valueOf(164));
        lru.put(33, 36);
        lru.put(85, 190);
        assertEquals(lru.get(10), Integer.valueOf(288));
        lru.put(52, 182);
        lru.put(76, 182);
        assertEquals(lru.get(109), Integer.valueOf(82));
        assertEquals(lru.get(118), Integer.valueOf(2));
        lru.put(82, 301);
        lru.put(26, 158);
        assertNull(lru.get(71));
        lru.put(108, 309);
        lru.put(58, 132);
        lru.put(13, 299);
        lru.put(117, 183);
        assertEquals(lru.get(115), Integer.valueOf(164));
        assertEquals(lru.get(89), Integer.valueOf(299));
        assertEquals(lru.get(42), Integer.valueOf(137));
        lru.put(11, 285);
        lru.put(30, 144);
        assertEquals(lru.get(69), Integer.valueOf(295));
        lru.put(31, 53);
        assertEquals(lru.get(21), Integer.valueOf(139));
        lru.put(96, 162);
        lru.put(4, 227);
        lru.put(77, 120);
        lru.put(128, 136);
        assertNull(lru.get(92));
        lru.put(119, 208);
        lru.put(87, 61);
        lru.put(9, 40);
        lru.put(48, 273);
        assertEquals(lru.get(95), Integer.valueOf(101));
        assertEquals(lru.get(35), Integer.valueOf(65));
        lru.put(62, 267);
        lru.put(88, 161);
        assertEquals(lru.get(59), Integer.valueOf(249));
        assertEquals(lru.get(85), Integer.valueOf(190));
        lru.put(131, 53);
        lru.put(114, 98);
        lru.put(90, 257);
        lru.put(108, 46);
        assertNull(lru.get(54));
        lru.put(128, 223);
        lru.put(114, 168);
        lru.put(89, 203);
        assertNull(lru.get(100));
        assertNull(lru.get(116));
        assertEquals(lru.get(14), Integer.valueOf(151));
        lru.put(61, 104);
        lru.put(44, 161);
        lru.put(60, 132);
        lru.put(21, 310);
        assertEquals(lru.get(89), Integer.valueOf(203));
        lru.put(109, 237);
        assertEquals(lru.get(105), Integer.valueOf(90));
        assertEquals(lru.get(32), Integer.valueOf(88));
        lru.put(78, 101);
        lru.put(14, 71);
        lru.put(100, 47);
        lru.put(102, 33);
        lru.put(44, 29);
        assertEquals(lru.get(85), Integer.valueOf(190));
        assertEquals(lru.get(37), Integer.valueOf(160));
        lru.put(68, 175);
        lru.put(116, 182);
        lru.put(42, 47);
        assertEquals(lru.get(9), Integer.valueOf(40));
        lru.put(64, 37);
        lru.put(23, 32);
        lru.put(11, 124);
        lru.put(130, 189);
        assertEquals(lru.get(65), Integer.valueOf(24));
        lru.put(33, 219);
        lru.put(79, 253);
        assertEquals(lru.get(80), Integer.valueOf(132));
        assertEquals(lru.get(16), Integer.valueOf(30));
        lru.put(38, 18);
        lru.put(35, 67);
        assertNull(lru.get(107));
        assertEquals(lru.get(88), Integer.valueOf(161));
        lru.put(37, 13);
        lru.put(71, 188);
        assertEquals(lru.get(35), Integer.valueOf(67));
        lru.put(58, 268);
        lru.put(18, 260);
        lru.put(73, 23);
        lru.put(28, 102);
        assertEquals(lru.get(129), Integer.valueOf(119));
        assertEquals(lru.get(88), Integer.valueOf(161));
        assertEquals(lru.get(65), Integer.valueOf(24));
        assertEquals(lru.get(80), Integer.valueOf(132));
        lru.put(119, 146);
        assertNull(lru.get(113));
        assertEquals(lru.get(62), Integer.valueOf(267));
        lru.put(123, 138);
        lru.put(18, 1);
        lru.put(26, 208);
        assertNull(lru.get(107));
        assertNull(lru.get(107));
        lru.put(76, 132);
        lru.put(121, 191);
        assertEquals(lru.get(4), Integer.valueOf(227));
        assertNull(lru.get(8));
        assertEquals(lru.get(117), Integer.valueOf(183));
        lru.put(11, 118);
        assertEquals(lru.get(43), Integer.valueOf(311));
        assertEquals(lru.get(69), Integer.valueOf(295));
        assertNull(lru.get(136));
        lru.put(66, 298);
        assertEquals(lru.get(25), Integer.valueOf(167));
        assertEquals(lru.get(71), Integer.valueOf(188));
        assertEquals(lru.get(100), Integer.valueOf(47));
        lru.put(26, 141);
        lru.put(53, 256);
        lru.put(111, 205);
        lru.put(126, 106);
        assertEquals(lru.get(43), Integer.valueOf(311));
        lru.put(14, 39);
        lru.put(44, 41);
        lru.put(23, 230);
        assertEquals(lru.get(131), Integer.valueOf(53));
        assertEquals(lru.get(53), Integer.valueOf(256));
        lru.put(104, 268);
        assertEquals(lru.get(30), Integer.valueOf(144));
        lru.put(108, 48);
        lru.put(72, 45);
        assertEquals(lru.get(58), Integer.valueOf(268));
        assertNull(lru.get(46));
        lru.put(128, 301);
        assertEquals(lru.get(71), Integer.valueOf(188));
        assertEquals(lru.get(99), Integer.valueOf(233));
        assertNull(lru.get(113));
        assertEquals(lru.get(121), Integer.valueOf(191));
        lru.put(130, 122);
        lru.put(102, 5);
        lru.put(111, 51);
        lru.put(85, 229);
        lru.put(86, 157);
        lru.put(82, 283);
        lru.put(88, 52);
        lru.put(136, 105);
        assertNull(lru.get(40));
        assertNull(lru.get(63));
        lru.put(114, 244);
        lru.put(29, 82);
        lru.put(83, 278);
        assertEquals(lru.get(131), Integer.valueOf(53));
        lru.put(56, 33);
        assertEquals(lru.get(123), Integer.valueOf(138));
        assertEquals(lru.get(11), Integer.valueOf(118));
        assertEquals(lru.get(119), Integer.valueOf(146));
        lru.put(119, 1);
        lru.put(48, 52);
        assertNull(lru.get(47));
        lru.put(127, 136);
        lru.put(78, 38);
        lru.put(117, 64);
        lru.put(130, 134);
        lru.put(93, 69);
        lru.put(70, 98);
        assertEquals(lru.get(68), Integer.valueOf(175));
        lru.put(4, 3);
        lru.put(92, 173);
        lru.put(114, 65);
        lru.put(7, 309);
        assertEquals(lru.get(31), Integer.valueOf(53));
        lru.put(107, 271);
        lru.put(110, 69);
        assertNull(lru.get(45));
        lru.put(35, 288);
        assertNull(lru.get(20));
        lru.put(38, 79);
        assertNull(lru.get(46));
        lru.put(6, 123);
        assertNull(lru.get(19));
        lru.put(84, 95);
        assertEquals(lru.get(76), Integer.valueOf(132));
        lru.put(71, 31);
        lru.put(72, 171);
        lru.put(35, 123);
        assertEquals(lru.get(32), Integer.valueOf(88));
        lru.put(73, 85);
        assertNull(lru.get(94));
        assertEquals(lru.get(128), Integer.valueOf(301));
        assertEquals(lru.get(28), Integer.valueOf(102));
        assertEquals(lru.get(38), Integer.valueOf(79));
        assertEquals(lru.get(109), Integer.valueOf(237));
        lru.put(85, 197);
        lru.put(10, 41);
        lru.put(71, 50);
        assertEquals(lru.get(128), Integer.valueOf(301));
        lru.put(3, 55);
        lru.put(15, 9);
        lru.put(127, 215);
        assertEquals(lru.get(17), Integer.valueOf(104));
        assertEquals(lru.get(37), Integer.valueOf(13));
        lru.put(111, 272);
        lru.put(79, 169);
        lru.put(86, 206);
        lru.put(40, 264);
        assertNull(lru.get(134));
        lru.put(16, 207);
        lru.put(27, 127);
        lru.put(29, 48);
        lru.put(32, 122);
        lru.put(15, 35);
        lru.put(117, 36);
        assertEquals(lru.get(127), Integer.valueOf(215));
        assertNull(lru.get(36));
        lru.put(72, 70);
        lru.put(49, 201);
        lru.put(89, 215);
        lru.put(134, 290);
        lru.put(77, 64);
        lru.put(26, 101);
        assertEquals(lru.get(99), Integer.valueOf(233));
        lru.put(36, 96);
        lru.put(84, 129);
        lru.put(125, 264);
        assertEquals(lru.get(43), Integer.valueOf(311));
        assertEquals(lru.get(38), Integer.valueOf(79));
        lru.put(24, 76);
        lru.put(45, 2);
        lru.put(32, 24);
        lru.put(84, 235);
        lru.put(16, 240);
        lru.put(17, 289);
        lru.put(49, 94);
        lru.put(90, 54);
        lru.put(88, 199);
        assertEquals(lru.get(23), Integer.valueOf(230));
        lru.put(87, 19);
        lru.put(11, 19);
        assertEquals(lru.get(24), Integer.valueOf(76));
        assertEquals(lru.get(57), Integer.valueOf(188));
        assertEquals(lru.get(4), Integer.valueOf(3));
        assertEquals(lru.get(40), Integer.valueOf(264));
        lru.put(133, 286);
        lru.put(127, 231);
        assertNull(lru.get(51));
        lru.put(52, 196);
        assertEquals(lru.get(27), Integer.valueOf(127));
        assertEquals(lru.get(10), Integer.valueOf(41));
        assertEquals(lru.get(93), Integer.valueOf(69));
        lru.put(115, 143);
        lru.put(62, 64);
        lru.put(59, 200);
        lru.put(75, 85);
        lru.put(7, 93);
        lru.put(117, 270);
        lru.put(116, 6);
        assertEquals(lru.get(32), Integer.valueOf(24));
        assertNull(lru.get(135));
        lru.put(2, 140);
        lru.put(23, 1);
        lru.put(11, 69);
        lru.put(89, 30);
        lru.put(27, 14);
        assertEquals(lru.get(100), Integer.valueOf(47));
        assertEquals(lru.get(61), Integer.valueOf(104));
        lru.put(99, 41);
        lru.put(88, 12);
        assertNull(lru.get(41));
        lru.put(52, 203);
        assertEquals(lru.get(65), Integer.valueOf(24));
        lru.put(62, 78);
        lru.put(104, 276);
        lru.put(105, 307);
        assertEquals(lru.get(7), Integer.valueOf(93));
        lru.put(23, 123);
        assertNull(lru.get(22));
        lru.put(35, 299);
        assertEquals(lru.get(69), Integer.valueOf(295));
        assertEquals(lru.get(11), Integer.valueOf(69));
        lru.put(14, 112);
        assertEquals(lru.get(115), Integer.valueOf(143));
        assertEquals(lru.get(112), Integer.valueOf(86));
        assertEquals(lru.get(108), Integer.valueOf(48));
        lru.put(110, 165);
        lru.put(83, 165);
        lru.put(36, 260);
        lru.put(54, 73);
        assertEquals(lru.get(36), Integer.valueOf(260));
        lru.put(93, 69);
        assertEquals(lru.get(134), Integer.valueOf(290));
        lru.put(125, 96);
        lru.put(74, 127);
        lru.put(110, 305);
        lru.put(92, 309);
        lru.put(87, 45);
        lru.put(31, 266);
        assertEquals(lru.get(10), Integer.valueOf(41));
        lru.put(114, 206);
        lru.put(49, 141);
        assertEquals(lru.get(82), Integer.valueOf(283));
        lru.put(92, 3);
        lru.put(91, 160);
        assertNull(lru.get(41));
        lru.put(60, 147);
        lru.put(36, 239);
        lru.put(23, 296);
        lru.put(134, 120);
        assertEquals(lru.get(6), Integer.valueOf(123));
        lru.put(5, 283);
        lru.put(117, 68);
        assertEquals(lru.get(35), Integer.valueOf(299));
        assertNull(lru.get(120));
        lru.put(44, 191);
        lru.put(121, 14);
        lru.put(118, 113);
        lru.put(84, 106);
        assertEquals(lru.get(23), Integer.valueOf(296));
        lru.put(15, 240);
        assertEquals(lru.get(37), Integer.valueOf(13));
        lru.put(52, 256);
        lru.put(119, 116);
        lru.put(101, 7);
        lru.put(14, 157);
        lru.put(29, 225);
        lru.put(4, 247);
        lru.put(8, 112);
        lru.put(8, 189);
        lru.put(96, 220);
        assertEquals(lru.get(104), Integer.valueOf(276));
        lru.put(72, 106);
        lru.put(23, 170);
        lru.put(67, 209);
        lru.put(70, 39);
        assertEquals(lru.get(18), Integer.valueOf(1));
        assertEquals(lru.get(6), Integer.valueOf(123));
        assertNull(lru.get(34));
        lru.put(121, 157);
        assertEquals(lru.get(16), Integer.valueOf(240));
        assertNull(lru.get(19));
        lru.put(83, 283);
        lru.put(13, 22);
        lru.put(33, 143);
        lru.put(88, 133);
        assertEquals(lru.get(88), Integer.valueOf(133));
        lru.put(5, 49);
        assertEquals(lru.get(38), Integer.valueOf(79));
        assertEquals(lru.get(110), Integer.valueOf(305));
        assertEquals(lru.get(67), Integer.valueOf(209));
        lru.put(23, 227);
        assertEquals(lru.get(68), Integer.valueOf(175));
        assertEquals(lru.get(3), Integer.valueOf(55));
        lru.put(27, 265);
        assertEquals(lru.get(31), Integer.valueOf(266));
        lru.put(13, 103);
        assertEquals(lru.get(116), Integer.valueOf(6));
        lru.put(111, 282);
        lru.put(43, 71);
        assertEquals(lru.get(134), Integer.valueOf(120));
        lru.put(70, 141);
        assertEquals(lru.get(14), Integer.valueOf(157));
        assertEquals(lru.get(119), Integer.valueOf(116));
        assertEquals(lru.get(43), Integer.valueOf(71));
        assertNull(lru.get(122));
        lru.put(38, 187);
        lru.put(8, 9);
        assertNull(lru.get(63));
        lru.put(42, 140);
        assertEquals(lru.get(83), Integer.valueOf(283));
        assertEquals(lru.get(92), Integer.valueOf(3));
        assertNull(lru.get(106));
        assertEquals(lru.get(28), Integer.valueOf(102));
        lru.put(57, 139);
        lru.put(36, 257);
        lru.put(30, 204);
        assertEquals(lru.get(72), Integer.valueOf(106));
        lru.put(105, 243);
        assertEquals(lru.get(16), Integer.valueOf(240));
        lru.put(74, 25);
        assertNull(lru.get(22));
        lru.put(118, 144);
        assertEquals(lru.get(133), Integer.valueOf(286));
        assertEquals(lru.get(71), Integer.valueOf(50));
        lru.put(99, 21);
        assertEquals(lru.get(26), Integer.valueOf(101));
        assertEquals(lru.get(35), Integer.valueOf(299));
        lru.put(89, 209);
        lru.put(106, 158);
        lru.put(76, 63);
        lru.put(112, 216);
        assertEquals(lru.get(128), Integer.valueOf(301));
        assertEquals(lru.get(54), Integer.valueOf(73));
        lru.put(16, 165);
        lru.put(76, 206);
        lru.put(69, 253);
        assertEquals(lru.get(23), Integer.valueOf(227));
        lru.put(54, 111);
        assertNull(lru.get(80));
        lru.put(111, 72);
        lru.put(95, 217);
        assertEquals(lru.get(118), Integer.valueOf(144));
        lru.put(4, 146);
        assertNull(lru.get(47));
        lru.put(108, 290);
        assertEquals(lru.get(43), Integer.valueOf(71));
        lru.put(70, 8);
        assertEquals(lru.get(117), Integer.valueOf(68));
        assertEquals(lru.get(121), Integer.valueOf(157));
        lru.put(42, 220);
        assertEquals(lru.get(48), Integer.valueOf(52));
        assertEquals(lru.get(32), Integer.valueOf(24));
        lru.put(68, 213);
        lru.put(30, 157);
        lru.put(62, 68);
        assertEquals(lru.get(58), Integer.valueOf(268));
        lru.put(125, 283);
        lru.put(132, 45);
        assertEquals(lru.get(85), Integer.valueOf(197));
        assertEquals(lru.get(92), Integer.valueOf(3));
        lru.put(23, 257);
        assertEquals(lru.get(74), Integer.valueOf(25));
        lru.put(18, 256);
        assertEquals(lru.get(90), Integer.valueOf(54));
        lru.put(10, 158);
        lru.put(57, 34);
        assertEquals(lru.get(27), Integer.valueOf(265));
        assertEquals(lru.get(107), Integer.valueOf(271));
    }
}

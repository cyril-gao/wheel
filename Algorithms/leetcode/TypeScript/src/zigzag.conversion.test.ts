import { convert } from "./zigzag.conversion";

test(
    "check the result value of the call to the function convert",
    () => {
        let result = convert("PAYPALISHIRING", 3);
        expect(result).toEqual("PAHNAPLSIIGYIR");
        result = convert("PAYPALISHIRING", 4);
        expect(result).toEqual("PINALSIGYAHRPI");
        result = convert("PAYPALISHIRING", 1);
        expect(result).toEqual("PAYPALISHIRING");
        result = convert("PAYPALISHIRING", 12);
        expect(result).toEqual("PAYPALISHIGRNI");
    }
);

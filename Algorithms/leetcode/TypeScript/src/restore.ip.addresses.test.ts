import { restoreIpAddresses } from "./restore.ip.addresses";

test(
    "check the result value of the call to the function restoreIpAddresses",
    () => {
        let result = restoreIpAddresses("25525511135");
        expect(result.length).toEqual(2);

        result = restoreIpAddresses("0000");
        expect(result.length).toEqual(1);

        result = restoreIpAddresses("00000");
        expect(result.length).toEqual(0);

        result = restoreIpAddresses("1111");
        expect(result.length).toEqual(1);

        result = restoreIpAddresses("010010");
        expect(result.length).toEqual(2);

        result = restoreIpAddresses("101023");
        expect(result.length).toEqual(5);
    }
);

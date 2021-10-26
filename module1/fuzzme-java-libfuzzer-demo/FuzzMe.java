package fuzzme;

public class FuzzMe {
    public static void fuzzerInitialize(){
        // any state initialization goes here!
    }

    public static void fuzzerTestOneInput(byte[] data) {
        String input = new String(data);

        if (input.length() >= 3 && input.length() < 5) {
            if (input.startsWith("b", 0)) {
                if (input.startsWith("u", 1)) {
                    if (input.startsWith("g", 2)) {
                        char x = input.charAt(10);
                    }
                }
            }
        }
    }
}
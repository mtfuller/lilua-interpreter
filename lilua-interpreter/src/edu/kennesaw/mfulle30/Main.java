// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 7 - 3rd Deliverable
// File:      Main.java
// Date:      04/20/17
// =============================================================================
// Description:
// This class includes the main method that runs the command-line application
// based on the arguments given by the user. The command-line application has 3
// flags to denote what the application should do:
//      -v  Display the version of the application
//      -h  Display help and usage information
//      -I  Run the interpreter for a given ".lil" input file, which is a file
//          that contains a fully compiled Lua program to be interpreted.
//
// The class also handles invalid or incorrect command-line arguments.
// =============================================================================

package edu.kennesaw.mfulle30;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Main {
    // Version Information
    public static final String NAME         =   "LiLua";
    public static final String VERSION      =   "v1.0";
    public static final String AUTHORS      =   "Thomas Fuller and Teddy Mopewou";
    public static final String DATE         =   "April 19, 2017";
    public static final String DESCRIPTION  =
            "The LiLua Interpreter command-line application. This application " +
                    "takes in a\ncompiled Lua file, denoted as a “.lil” file. ";

    // Help Information
    public static final String HELP_FORMAT = "\t%-13s   %-64s";
    public static final String HELP_INFORMATION  =
            "usage: lilua [options] [source file]\n" +
            String.format(HELP_FORMAT, "-v", "Display the current version and other information about the application.") + "\n" +
            String.format(HELP_FORMAT, "-h", "Prints the help message for the application.") + "\n" +
            String.format(HELP_FORMAT, "-I [pathname]", "Takes in a relative path to a compiled Lua file. The file is then interpreted") + "\n" +
            String.format(HELP_FORMAT, "", "immediately.") + "\n";

    public static void main(String[] args) {
        // Check to make sure there is at least 1 command-line argument
        if (args.length >= 1) {
            String flag = args[0];

            // Checks the value of the flag being passed in
            if (flag.equals("-v")) version();
            else if (flag.equals("-h")) help();
            else if (flag.equals("-I") && args.length == 2) {
                String filePath = args[1];

                // Interpret the file
                try {
                    interpret(filePath);
                } catch (IOException e) {
                    System.out.println("FILE NOT FOUND ERROR. File could not be located.");
                }
            } else {
                System.out.println("ERROR. Invalid arguments.");
                help();
            }
        }  else {
            System.out.println("ERROR. Too few arguments.");
            help();
        }
    }

    private static void interpret(String pathName) throws IOException {
        // Create a file path object to the source file to interpret
        Path inputFilePath = Paths.get(pathName);

        // Read all bytes in the file into a primative Java array
        byte[] data = Files.readAllBytes(inputFilePath);

        // Create and run the interpreter
        Interpreter interpreter = new Interpreter(data);
        interpreter.run();
    }

    private static void help() {
        // Display help and usage information
        System.out.println(HELP_INFORMATION);
    }

    private static void version() {
        // Display version information
        System.out.println(NAME + " " + VERSION + "\n");
        System.out.println("Authors:\t" + AUTHORS);
        System.out.println("Last Modified:\t" + DATE + "\n");
        System.out.println("Description:\n" + DESCRIPTION);
    }
}

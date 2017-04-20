package edu.kennesaw.ccse.mfulle30;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Stack;

/**
 * Created by Thomas on 4/19/2017.
 */
public class Interpreter {
    private Stack<DataValue> stack = new Stack<>();
    private LinkedList<Instruction> instructions = new LinkedList<>();
    private byte[] byteArray;
    private int[] symbolTable;

    private boolean isRunning = true;
    private int instructionPointer;

    public Interpreter(byte[] byteArray) {
        this.byteArray = byteArray;
        symbolTable = new int[26];
    }

    public void run() {
        // Go through all bytes in the array, 6 at a time, and build the list of instructions
        for (int i = 0; i < byteArray.length; i+=6) {
            byte[] instructionBytes = Arrays.copyOfRange(byteArray, i, i + 6);
            instructions.addLast(new Instruction(instructionBytes));
        }

        // Keep executing instructions until the end of the program was encountered
        while (instructionPointer < instructions.size() && isRunning) {
            try {
                // Execute the current instruction and increment the instruction pointer
                execute(instructions.get(instructionPointer++));
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("FAILED!!! @ IP:"+instructionPointer);
                return;
            }
        }

        // Tell the user that the program has finished
        System.out.println("\nFinished execution.");
    }

    private void execute(Instruction instruction) throws Exception {
        DataValue first, second;        // Data Values that are pushed/popped to the stack
        Integer operand1, operand2;     // Operands used for arithmetic and boolean expressions

        // Execute the instruction with its specific opCode
        switch (instruction.getOpCode()) {
            case Instruction.PUSH_OP:
                // Push Data Value onto the stack
                stack.push(instruction.getDataValue());
                break;
            case Instruction.POP_OP:
                // Pop the most recent Data Value from the stack
                stack.pop();
                break;
            case Instruction.ASSIGN_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Check if the bottom-most Data Value is an ID
                if (first.getType() != DataType.ID_TYPE) throw new Exception("Assignment Failed, ID type mismatch");

                // Add the top-most Data Value, whether ID or Literal Integer, to the ID of bottom-most Data Value
                if (second.getType() == DataType.INT_TYPE) {
                    symbolTable[first.getValue()] = second.getValue();
                } else if (second.getType() == DataType.ID_TYPE) {
                    symbolTable[first.getValue()] = symbolTable[second.getValue()];
                } else {
                    throw new Exception("Assignment Failed, RValue is not ID or INT");
                }
                break;
            case Instruction.ADD_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Push the value of the sum of the two operands
                stack.push(new DataValue(DataType.INT_TYPE, operand1 + operand2));
                break;
            case Instruction.SUB_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Push the value of the difference of the two operands
                stack.push(new DataValue(DataType.INT_TYPE, operand1 - operand2));
                break;
            case Instruction.MULT_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Push the value of the product of the two operands
                stack.push(new DataValue(DataType.INT_TYPE, operand1 * operand2));
                break;
            case Instruction.DIV_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Check for a Divide by Zero event
                if (operand2 == 0) throw new ArithmeticException("Divide by zero error");

                // Push the value of the quotient of the two operands
                stack.push(new DataValue(DataType.INT_TYPE, operand1 / operand2));
                break;
            case Instruction.GT_OPP_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 > operand2) ? 0 : 1));
                break;
            case Instruction.GE_OPP_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 >= operand2) ? 0 : 1));
                break;
            case Instruction.LT_OPP_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 < operand2) ? 0 : 1));
                break;
            case Instruction.LE_OPP_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 <= operand2) ? 0 : 1));
                break;
            case Instruction.EQ_OPP_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 == operand2) ? 0 : 1));
                break;
            case Instruction.NOT_EQ_OP:
                // Pop the first two Data Values from the stack
                second = stack.pop();
                first = stack.pop();

                // Get each operand
                operand1 = getArithmeticOperand(first);
                operand2 = getArithmeticOperand(second);

                // Pushes the result of the boolean expression to the stack
                stack.push(new DataValue(DataType.BOOL_TYPE, (operand1 != operand2) ? 0 : 1));
                break;
            case Instruction.GOTO_OP:
                // Check to make sure than the GOTO address is of type Integer
                if (instruction.getDataValue().getType() != DataType.INT_TYPE)
                    throw new Exception("GOTO Failed, not given an integer");

                // Move instruction pointer to the relative GOTO address
                instructionPointer += instruction.getDataValue().getValue();
                break;
            case Instruction.GOFALSE_OP:
                // Pop a Data Value from the stack
                first = stack.pop();

                // Check to make sure that the popped Data Value is a boolean
                if (first.getType() != DataType.BOOL_TYPE)
                    throw new Exception("GOFALSE Failed, boolean not found on top of stack");

                // Check to make sure than the GOFALSE address is of type Integer
                if (instruction.getDataValue().getType() != DataType.INT_TYPE)
                    throw new Exception("GOFALSE Failed, not given an integer");

                // If the Data Value boolean was false, then move instruction pointer to the relative GOFALSE address
                if (!first.getBool()) instructionPointer += instruction.getDataValue().getValue();
                break;
            case Instruction.HALT_OP:
                // Terminate the interpreter
                isRunning = false;
                break;
            case Instruction.PRINT_OP:
                // Pop the most recent Data Value from the stack
                first = stack.pop();

                // Get the arithmetic operand from the most recent Data Value
                operand1 = getArithmeticOperand(first);

                // Print the operand to the screen
                System.out.println(operand1);
                break;
        }
    }

    private int getArithmeticOperand(DataValue dataValue) throws Exception {
        int val;
        if (dataValue.getType() == DataType.ID_TYPE) val = symbolTable[dataValue.getValue()];
        else if (dataValue.getType() == DataType.INT_TYPE) val = dataValue.getValue();
        else throw new Exception("Add Op Failed, type 1st operand mismatch");
        return val;
    }
}

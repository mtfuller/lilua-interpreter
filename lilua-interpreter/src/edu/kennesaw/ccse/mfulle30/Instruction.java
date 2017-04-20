package edu.kennesaw.ccse.mfulle30;

import java.nio.ByteBuffer;

/**
 * Created by Thomas on 4/19/2017.
 */
public class Instruction {
    public final static byte BOOL_TYPE 	= 1;
    public final static byte INT_TYPE 	= 2;
    public final static byte ID_TYPE 	= 3;

    public final static byte PUSH_OP 	= 0;
    public final static byte POP_OP 	= 1;
    public final static byte ASSIGN_OP 	= 2;
    public final static byte ADD_OP 	= 3;
    public final static byte SUB_OP 	= 4;
    public final static byte MULT_OP 	= 5;
    public final static byte DIV_OP 	= 6;
    public final static byte GT_OPP_OP 	= 7;
    public final static byte GE_OPP_OP 	= 8;
    public final static byte LT_OPP_OP 	= 9;
    public final static byte LE_OPP_OP 	= 10;
    public final static byte EQ_OPP_OP 	= 11;
    public final static byte NOT_EQ_OP 	= 12;
    public final static byte GOTO_OP 	= 13;
    public final static byte GOFALSE_OP = 14;
    public final static byte HALT_OP 	= 15;
    public final static byte PRINT_OP 	= 16;

    private byte opCode;
    private DataValue dataValue;

    public Instruction(byte[] instrBytes) {
        assert instrBytes.length == 6;
        opCode = instrBytes[0];
        DataType type;
        switch (instrBytes[1]) {
            case BOOL_TYPE:
                type = DataType.BOOL_TYPE;
                break;
            case INT_TYPE:
                type = DataType.INT_TYPE;
                break;
            case ID_TYPE:
                type = DataType.ID_TYPE;
                break;
            default:
                type = DataType.NULL_TYPE;
        }
        dataValue = new DataValue(type, bytesToInt(instrBytes[2], instrBytes[3], instrBytes[4], instrBytes[5]));
        //System.out.println(opCode+" "+type.name()+" "+dataValue.getValue());
    }

    public byte getOpCode() {
        return opCode;
    }

    public DataValue getDataValue() {
        return dataValue;
    }

    public static int bytesToInt(byte b1, byte b2, byte b3, byte b4) {
        // Create a byte array from the 4 bytes of data passed in
        byte[] arr = {b4,b3,b2,b1};

        // Use the ByteBuffer class to "wrap" the array into a new Java primitive int
        int result = ByteBuffer.wrap(arr).getInt();

        // Return an int equal to the value of the result
        return result;
    }
}

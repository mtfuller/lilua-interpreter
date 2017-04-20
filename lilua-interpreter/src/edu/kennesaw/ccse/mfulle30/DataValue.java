package edu.kennesaw.ccse.mfulle30;

/**
 * Created by Thomas on 4/19/2017.
 */
public class DataValue {
    private DataType type;
    private int value;

    public DataValue(DataType type, int value) {
        this.type = type;
        this.value = value;
    }

    public DataType getType() {
        return type;
    }

    public int getValue() {
        return value;
    }

    public boolean getBool() {
        if (value == 0) return true;
        else return false;
    }
}

// =============================================================================
// Author(s): Thomas Fuller
// Course:    CS 4308 (01)
// Instr:     Dr. Garrido
// Project:   Module 7 - 3rd Deliverable
// File:      DataValue.java
// Date:      04/20/17
// =============================================================================
// Description:
// This class defines the "Data Value" that is found in an instruction. Each
// DataValue object needs to hold the type (i.e. null, boolean, int, or ID) and
// the numerical value of the instrction's Data Value.
// =============================================================================

package edu.kennesaw.mfulle30;

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

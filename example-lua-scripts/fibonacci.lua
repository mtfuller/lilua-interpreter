function f(count)
    -- RPN: > count 0
    if count > 0 then
        a = 0
        b = 1
        print(a)
        -- RPN: == count 1
        if count == 1 then
            -- RPN: count = - count 1
            count = count - 1
        else
            print(b)
            -- RPN: == count 2
            if count == 2 then
                -- RPN: count = - count 1
                count = count - 1
            else
                c = 0
                -- RPN: count = - count 2
                count = count - 2
                while count > 0 do
                    c = a + b
                    a = b
                    b = c
                    print(c)
                    -- RPN: count = - count 1
                    count = count - 1
                end
            end
        end
    else
        print(0)
    end
end

f(8)

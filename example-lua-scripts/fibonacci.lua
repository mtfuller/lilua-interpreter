function f(n)
    -- RPN: > n 0
    if n > 0 then
        a = 0
        b = 1
        print(a)
        -- RPN: == n 1
        if n == 1 then
            -- RPN: n = - n 1
            n = n - 1
        else
            print(b)
            -- RPN: == n 2
            if n == 2 then
                -- RPN: n = - n 1
                n = n - 1
            else
                c = 0
                -- RPN: n = - n 2
                n = n - 2
                while n > 0 do
                    c = a + b
                    a = b
                    b = c
                    print(c)
                    -- RPN: n = - n 1
                    n = n - 1
                end
            end
        end
    else
        print(0)
    end
end

f(8)

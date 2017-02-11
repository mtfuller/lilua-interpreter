function f()
  n = 100
  c = 1
  repeat
    -- Modulus operation in pure arithmetic ops:
    -- RPN: r = - c * 2 / c 2
    --          - c * 2 c/2
    --          - c 2*(c/2)
    --          c-2*(c/2)
    r = c - 2 * math.floor(c / 2)
    -- RPN: == r 0
    if r == 0 then
      print(c)
      -- RPN: c = + c 1
      c = c + 1
    else
      -- RPN: c = + c 1
      c = c + 1
    end
  -- RPN: > c n
  until c > n
end

f()

function f()
  n = 100
  c = 1
  repeat
    -- Modulus operation in pure arithmetic ops:
    r = c - 2 * c / 2
    if r == 0 then
      print(c)
      c = c + 1
    else
      c = c + 1
    end
  until c > n
end

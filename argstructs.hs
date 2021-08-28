import Data.List
import Text.Printf

listInts :: Show a => [a] -> String -> String -> String
listInts items sep ends =
    printf "%s%s%s" begin (intercalate sep $ map show items) end
    where
        begin = take 1 ends
        end = take 1 $ tail ends

main = putStrLn $ listInts [1, 2, 3] ", " "[]"

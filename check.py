import enchant

dict = enchant.Dict("en-US")

print(dict.check("text"))
with open("/Users/hanyuzhang/CLionProjects/Sketch/words", "r") as words:
    with open("/Users/hanyuzhang/CLionProjects/Sketch/correct", "w") as correct:
        for word in words:
            if dict.check(''.join(filter(str.isalpha, word))) == True:
                correct.write(word)
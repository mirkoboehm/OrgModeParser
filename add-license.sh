for FILE in `find . -name "*.cpp" -o -name "*.h"`; do 
    if grep -q "OrgModeParser is free software: you can redistribute it and/or" $FILE; then
	# skip this file, it already has a license header
	echo $FILE already has a license header.
    else
	cat LICENSE.default $FILE > $FILE.new
	mv $FILE.new $FILE
	echo Added license information to $FILE.
    fi
done

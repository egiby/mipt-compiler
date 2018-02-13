for f in ./stuff/BadSamples/*.java
do
echo $f
./tmp/type_checker $f 
done

numA=$1
numB=$2
echo "Parameter A passed is $numA"
echo "Parameter B passed is $numB"
if [ "$numA" -eq "$numB" ]; then
  echo "Parameter A and B are equal"
elif [ $numA -lt $numB ]
then
  echo "Parameter A is equal to B"
  for ((i = $numA; i <= $numB; i++)); do
    echo "$i"
  done
elif [ $numA -gt $numB ]
then
  echo "Parameter A is greater than Parameter B"
  for ((i = $numB; i <= $numA; i++)); do
    echo "$i"
  done
fi
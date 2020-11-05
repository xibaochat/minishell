echo
echo "TEST >"
echo 

echo essai 1 : "jojo > prout"
echo 
echo jojo > prout
echo "cat prout"
cat prout
echo should display :
echo jojo

echo 
echo essai 2 : "jojo >> prout"
echo 
echo jojo >> prout
echo "cat prout"
cat prout
echo should display :
echo
echo "rm prout"
rm prout
echo should display :
echo jojo
echo jojo

echo 
echo essai 3 : "jojo >prout > lulu"
echo 
echo jojo >prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo jojo

echo 
echo essai 4 : "titi > prout > lulu"
echo 
echo titi > prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo 
echo essai 5 : "lala> prout > lulu"
echo 
echo lala> prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo lala

echo 
echo essai 6 : "titi>prout > lulu"
echo 
echo titi>prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo 
echo essai 7 : "titi>prout>lulu"
echo 
echo titi>prout>lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo
echo "TEST >>"
echo 

echo 
echo essai 8 : "jojo >>prout > lulu"
echo 
echo jojo >>prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo jojo

echo 
echo essai 9 : "titi >> prout > lulu"
echo 
echo titi >> prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo 
echo essai 10 : "lala>> prout > lulu"
echo 
echo lala>> prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo lala

echo 
echo essai 11 : "titi>>prout > lulu"
echo 
echo titi>>prout > lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo 
echo essai 12 : "titi>>prout>lulu"
echo 
echo titi>>prout>lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi

echo 
echo essai 13 : "titi>>prout>>lulu"
echo 
echo titi>>prout>>lulu
echo "cat prout"
cat prout
echo should display :
echo "cat lulu"
cat lulu
echo should display :
echo titi
echo titi

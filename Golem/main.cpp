#include <iostream>	// For string
#include "Printer.h"

// Included functions
void print(std::string str);

int main() {
	// Contained within dec is the US Declaration of Independence
	/*std::string dec{ "The unanimous Declaration of the thirteen united States of America, When in the \
Course of human events, it becomes necessary for one people to dissolve the poli\
tical bands which have connected them with another, and to assume among the powe\
rs of the earth, the separate and equal station to which the Laws of Nature and \
of Nature's God entitle them, a decent respect to the opinions of mankind requir\
es that they should declare the causes which impel them to the separation. We ho\
ld these truths to be self-evident, that all men are created equal, that they ar\
e endowed by their Creator with certain unalienable Rights, that among these are\
Life, Liberty and the pursuit of Happiness. That to secure these rights, Govern\
ments are instituted among Men, deriving their just powers from the consent of t\
he governed, That whenever any Form of Government becomes destructive of these e\
nds, it is the Right of the People to alter or to abolish it, and to institute n\
ew Government, laying its foundation on such principles and organizing its power\
s in such form, as to them shall seem most likely to effect their Safety and Hap\
piness. Prudence, indeed, will dictate that Governments long established should \
not be changed for light and transient causes; and accordingly all experience ha\
th shewn, that mankind are more disposed to suffer, while evils are sufferable, \
than to right themselves by abolishing the forms to which they are accustomed. B\
ut when a long train of abuses and usurpations, pursuing invariably the same Obj\
ect evinces a design to reduce them under absolute Despotism, it is their right,\
it is their duty, to throw off such Government, and to provide new Guards for t\
heir future security. Such has been the patient sufferance of these Colonies; an\
d such is now the necessity which constrains them to alter their former Systems \
of Government. The history of the present King of Great Britain is a history of \
repeated injuries and usurpations, all having in direct object the establishment\
of an absolute Tyranny over these States. To prove this, let Facts be submitted\
to a candid world. He has refused his Assent to Laws, the most wholesome and ne\
cessary for the public good. He has forbidden his Governors to pass Laws of imme\
diate and pressing importance, unless suspended in their operation till his Asse\
nt should be obtained; and when so suspended, he has utterly neglected to attend\
to them. He has refused to pass other Laws for the accommodation of large distr\
icts of people, unless those people would relinquish the right of Representation\
in the Legislature, a right inestimable to them and formidable to tyrants only.\
He has called together legislative bodies at places unusual, uncomfortable, and\
distant from the depository of their public Records, for the sole purpose of fa\
tiguing them into compliance with his measures. He has dissolved Representative \
Houses repeatedly, for opposing with manly firmness his invasions on the rights \
of the people. He has refused for a long time, after such dissolutions, to cause\
others to be elected; whereby the Legislative powers, incapable of Annihilation\
, have returned to the People at large for their exercise; the State remaining i\
n the mean time exposed to all the dangers of invasion from without, and convuls\
ions within. He has endeavoured to prevent the population of these States; for t\
hat purpose obstructing the Laws for Naturalization of Foreigners; refusing to p\
ass others to encourage their migrations hither, and raising the conditions of n\
ew Appropriations of Lands. He has obstructed the Administration of Justice, by \
refusing his Assent to Laws for establishing Judiciary powers. He has made Judge\
s dependent on his Will alone, for the tenure of their offices, and the amount a\
nd payment of their salaries. He has erected a multitude of New Offices, and sen\
t hither swarms of Officers to harrass our people, and eat out their substance. \
He has kept among us, in times of peace, Standing Armies without the Consent of \
our legislatures. He has affected to render the Military independent of and supe\
rior to the Civil power. He has combined with others to subject us to a jurisdic\
tion foreign to our constitution, and unacknowledged by our laws; giving his Ass\
ent to their Acts of pretended Legislation: For Quartering large bodies of armed\
troops among us: For protecting them, by a mock Trial, from punishment for any \
Murders which they should commit on the Inhabitants of these States: For cutting\
off our Trade with all parts of the world: For imposing Taxes on us without our\
Consent: For depriving us in many cases, of the benefits of Trial by Jury: For \
transporting us beyond Seas to be tried for pretended offences For abolishing th\
e free System of English Laws in a neighbouring Province, establishing therein a\
n Arbitrary government, and enlarging its Boundaries so as to render it at once \
an example and fit instrument for introducing the same absolute rule into these \
Colonies: For taking away our Charters, abolishing our most valuable Laws, and a\
ltering fundamentally the Forms of our Governments: For suspending our own Legis\
latures, and declaring themselves invested with power to legislate for us in all\
cases whatsoever. He has abdicated Government here, by declaring us out of his \
Protection and waging War against us. He has plundered our seas, ravaged our Coa\
sts, burnt our towns, and destroyed the lives of our people. He is at this time \
transporting large Armies of foreign Mercenaries to compleat the works of death,\
desolation and tyranny, already begun with circumstances of Cruelty & perfidy s\
carcely paralleled in the most barbarous ages, and totally unworthy the Head of \
a civilized nation. He has constrained our fellow Citizens taken Captive on the \
high Seas to bear Arms against their Country, to become the executioners of thei\
r friends and Brethren, or to fall themselves by their Hands. He has excited dom\
estic insurrections amongst us, and has endeavoured to bring on the inhabitants \
of our frontiers, the merciless Indian Savages, whose known rule of warfare, is \
an undistinguished destruction of all ages, sexes and conditions. In every stage\
of these Oppressions We have Petitioned for Redress in the most humble terms: O\
ur repeated Petitions have been answered only by repeated injury. A Prince whose\
character is thus marked by every act which may define a Tyrant, is unfit to be\
the ruler of a free people. Nor have We been wanting in attentions to our Britt\
ish brethren. We have warned them from time to time of attempts by their legisla\
ture to extend an unwarrantable jurisdiction over us. We have reminded them of t\
he circumstances of our emigration and settlement here. We have appealed to thei\
r native justice and magnanimity, and we have conjured them by the ties of our c\
ommon kindred to disavow these usurpations, which, would inevitably interrupt ou\
r connections and correspondence. They too have been deaf to the voice of justic\
e and of consanguinity. We must, therefore, acquiesce in the necessity, which de\
nounces our Separation, and hold them, as we hold the rest of mankind, Enemies i\
n War, in Peace Friends. We, therefore, the Representatives of the united States\
    of America, in General Congress, Assembled, appealing to the Supreme Judge of t\
he world for the rectitude of our intentions, do, in the Name, and by Authority \
of the good People of these Colonies, solemnly publish and declare, That these U\
nited Colonies are, and of Right ought to be Free and Independent States; that t\
hey are Absolved from all Allegiance to the British Crown, and that all politica\
l connection between them and the State of Great Britain, is and ought to be tot\
ally dissolved; and that as Free and Independent States, they have full Power to\
levy War, conclude Peace, contract Alliances, establish Commerce, and to do all\
other Acts and Things which Independent States may of right do. And for the sup\
port of this Declaration, with a firm reliance on the protection of divine Provi\
dence, we mutually pledge to each other our Lives, our Fortunes and our sacred H\
onor." };*/
	std::string dec{ "This is a much more manageable test string." };
	print(dec);
}
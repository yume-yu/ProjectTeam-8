/**
 * @file storytext.h
 * @brief ゲーム内でアニメーション表示する文章の内、シナリオに関連するものをまとめたヘッダ
 * @author yume_yu
 * @date
 */

#include "thebeautifulsky.h"

/**
 * 構造体 extendstr について
 * 宣言はこんな感じ make_for_game.h:214-218
 * extendstr{
 * 表示する文字列(一行分)。必ず文の最後に半角スペースを入れないと、最後の1文字が抜けるので注意
 * char string[100];
 * 開始位置のズレ。一文を分割したときに後半を任意の位置ずらせる
 * int offset;
 * 入力待機が不要かどうかのフラグ。ここを1にすると、その行を最後まで表示した後Enterを押さなくても次の行の表示が始まる。
 * int not_need_return;
 * };
 */

extendstr subtitle1[] = {
	{"　第一章　プロローグ ",0,1},
	{"▼  ",20,0}
};
extendstr subtitle2[] = {
	{"　第二章　貴方と共に ",0,1},
	{"▼  ",20,0}
};
extendstr subtitle3[] = {
	{"　第三章　裁きの天秤 ",0,1},
	{"▼  ",20,0}
};
extendstr subtitle4[] = {
	{"　第四章　神の奇跡は偉大なり ",0,1},
	{"▼  ",26,0}
};
extendstr subtitle5[] = {
	{"　第五章　この広い世界で貴方と一緒に ",0,1},
	{"▼  ",34,0}
};

/* ステージ1 プロローグ */
extendstr cenario_stage1[] ={
	{"ここは空の上浮かぶ島、オルディン▼ ",0,0},
	{"陽気な気候に保たれた風の国の中で ",0,1},
	{"最も気候がおだやかな場所である▼ ",26,0},
	{"しかし、島の平穏は ",0,1},
	{"黒い雲と共に現れた無数の飛行船によって突如崩れ去った▼ ",4,0},
};

/* ステージ1 誘導 */
extendstr lirel_said[] = {
	{"リーレル：「建物等が崩れている. . .  ",0,1},
	{"早く姫と祭壇に行かなくては」▼ ",12,0}
};

/* ステージ1 侵入禁止 */
extendstr lirel_stop[] = {
	{"リーレル：「今はそれどころではない ",0,1},
	{"一刻も早く逃げなければ」▼ ",20,0}
};

/* ステージ1 ボス戦前 */
extendstr beforebattle_stage1[] = {
	{"リーレル：「ここにも追手が…やむを得ん、行くぞ！」▼ ",0},
};

/* ステージ1 ボス戦後 */
extendstr afterbattle_stage1[] = {
	{"アリスト：「見てリーレル動くよ」▼ ",0},
	{"リーレル：「・・・姫」▼ ",0},
	{"突然の襲撃に為す術なく、地上へ逃れた姫と騎士▼ ",0},
	{"そこはかつての大戦によって荒れ果てた世界だった。▼ ",0},
	{"その世界でアリストはナオキと出会う。▼ ",0}
};

/* ステージ2 プロローグ */
extendstr cenario_stage2[] ={
	{"リーレルとはぐれてしまったアリストは、 ",0,1},
	{"地上で人間のナオキと出会い、 ",4,1},
	{"人間がまだ生きている事を知った。▼ ",8,0},
	{"リーレルを探さねばならないが、 ",0,1},
	{"地上の地理を全く知らないアリストは ",0,1},
	{"ナオキと行動を共にし人間の國々を回った。▼ ",4,0},
	{"その道中、 ",0,1},
	{"ナオキが南方の国オルタナティブの第一王子だと知り、 ",4,1},
	{"彼のため王選に協力することを決める。▼ ",4,0},
	{"しかし、王戦とは候補者同士で雌雄を決する儀式だった▼ ",0,1},
	{"アリストは候補唯一人を守る協力者として ",0,1},
	{"忠義の証である呪術をその身に受ける。▼ ",20,0},
};

/* ステージ2 右の家内シナリオ1 */
extendstr talk_st2_0_1[] ={
	{"アリスト：「貴方達人間は ",0,1},
	{"どんな暮らしをしているの？」▼  ",10,0},
	{"この質問に対してナオキは",0,1},
	{"声を高らかにして笑っていた。▼  ",14,0},
	{"ナオキ：「いや悪い、馬鹿にしたとかじゃない。 ",0,1},
	{"まさか、そんな事を聞いてくるとは思わなくて ",8,1},
	{"つい笑ってしまった。」▼   ",14,0},
	{"アリスト：「私生まれてから一度も外に出たことがないの、 ",0,1},
	{"だから外の世界がどうなっているのか知りたいの ",14,1},
	{"私にこの世界の事を教えて」▼  ",0,0},
	{"アリストの表\情は好奇心に満ちあふれていた ",0,1},
	{"まるで、自分自身を見ているみたいだ ",10,1},
	{"ナオキは感じていた。▼  ",18,0},
	{"ナオキ：「人間は地上では生きる事ができず ",0,1},
	{"地下へ逃げ５つの國を作りあげた。 ",8,1},
	{"地下での暮らしは自給自足で暮らしている。」▼  ",10,0},
	{"ナオキ：「俺は人間はこの地に拘束されていると ",0,1},
	{"俺は思っている」▼  ",18,0},
	{"ナオキ：「地下に國を作り、 ",0,1},
	{"その中でしか生きる事ができない。▼  ",8,0},
};

/* ステージ2 右の家内シナリオ2 */
extendstr talk_st2_0_2[] ={
	{"まるで、牢獄みたいだろ。」▼  ",10,0},
	{"アリスト：「牢獄ね、けどこの國を見ていると ",0,1},
	{"民は幸せな感じがする、 ",10,1},
	{"それだけで良い國だと感じるわ」▼  ",14,0},
	{"ナオキ：「そんなものか。俺には良くわからないな。」▼  ",0,0},
};

extendstr beforebattle_stage2[] ={
	{"王戦で彼らを待っていたのは ",0,1},
	{"対戦相手であるタクトと協力者であるリーレルであった。▼ ",0,0},
	{"４人の実力はほぼ互角で死闘を繰り広げた。▼ ",10,0},
	{"その時、一瞬の隙をついて凶刃がアリストに迫る。▼ ",0,0},
	{"しかし、凶刃を受けたのは ",0,1},
	{"咄嗟に彼女をかばったリーレルであった。▼ ",14,0},
	{"リーレル：「これでよい。後悔はない。 ",0,1},
	{"これが偽らざる私の本音なのだから ",12,1},
	{"姫、私は常に貴女と共に」 ",16,1},
	{"姫への忠誠の言葉を残し、 ",0,1},
	{"王選の呪術によりリーレルは命を落とした。▼ ",16,0},
	{"ナオキ：「すまないタクト…ここで終わらせてもらう！」▼ ",0,0},
};

/* ステージ2ボス戦後 */
extendstr afterbattle_stage2[] ={
	{"天地全てを満たす平和と繁栄を目指すナオキとアリスト。▼ ",0},
	{"オルタナティブをまとめあげたが先はまだ長い。▼ ",0},
	{"地上にいる人間こそ ",0,1},
	{"この世を統べるに価すると考えているアルタ大帝國 ",8,1},
	{"この帝國を倒さない限り先はない。▼ ",10,0},
	{"ナオキ：「小細工なんかいらない。シンプルに行こうぜ」▼ ",0,0},
};

/* ステージ3 プロローグ */
extendstr cenario_stage3[] ={
	{"時は流れて、３年、 ",8,1},
	{"荒廃していく人の姿　▼ ",15,0},
	{"悪へ傾く天秤に　 ",16,1},
	{"私の胸は切なく激しく痛むのだ　 ",8,1},
	{"人の子よ、　 ",20,1},
	{"なぜ同胞で憎み合う。なぜ同胞で殺し合う　？  ▼  ",8,0},
	{"その姿を見てあの人は涙を流す。▼  ",0,0},
	{"ならばその咎、この手で裁こう。▼  ",10,0},
};

/* 左マップ一番左の家 */
extendstr talk_st3_0[] ={
	{"村人：「今はアルタ大帝國が夜もおちおち寝ていられない」▼ ",0,1},
	{"攻めてきているから ",8,1},
	{"夜もおちおち寝ていられない。」▼ ",0,0},
	{"村人：「王様どうするつもりなのか？」▼ ",0,0},
};

/* 左マップ下 銃の入手イベント 初回 */
extendstr talk_st3_1[] ={
	{"仲間：「ナオキ例の銃手に入ったぞ、 ",0,1},
	{"この銃の利点は２つ ",8,1},
	{"２回攻撃と弾薬が尽きないことだ。▼  ",10,0},
	{"持てる武器は１つだけなんだが、持っていくか？」 ",8,1}
};

/* 銃の入手イベント ２回め以降で銃を持っていなかった時 */
extendstr talk_st3_1_1[] ={
	{"仲間：「この銃の利点は２つ ",0,1},
	{"２回攻撃と弾薬が尽きないことだ。▼  ",10,0},
	{"やっぱり持っていく気になったか？」 ",8,1}
};

/* 銃の入手イベント 装備した時 */
extendstr talk_st3_1_2[] ={
	{"仲間：「大事に使ってやってくれ」▼ ",0,0},
};

/* 銃の入手イベント 装備しなかった時 */
extendstr talk_st3_1_3[] ={
	{"仲間：「そうか。必要ならまた来てくれ」▼ ",0,0},
};

/* 左マップ右上 防護服の入手イベント 初回 */
extendstr talk_st3_2[] ={
	{"仲間：「ナオキ念のため防護服着ていくか？」 ",0,1},
};

/* 防護服の入手イベント ２回め以降で持っていなかった時 */
extendstr talk_st3_2_1[] ={
	{"仲間：「念には念を、防護服着ていかないか？」 ",0,1},
};

/* 防護服の入手イベント 装備した時 */
extendstr talk_st3_2_2[] ={
	{"仲間：「気を付けてな」▼  ",0,0},
};

/* 防護服の入手イベント 装備しなかった時 */
extendstr talk_st3_2_3[] ={
	{"仲間：「そうか。必要ならまた来てくれ」▼  ",0,0},
};

/* 左マップ下 ナイフの入手イベント 初回 */
extendstr talk_st3_3[] ={
	{"仲間：「なにかと役に立つだろうし、 ",0,1},
	{"ナイフ持っていくかい？▼  ",16,0},
	{"もし持ってるものがあったら交換だけどな！」 ",8,1}
};

/* ナイフの入手イベント おまけポーション */
extendstr talk_st3_3_0[] ={
	{"仲間：「これから戦いに行くんだろう？▼ ",0,0},
	{"ならこいつは絶対いるはずだ」▼  ",10,0},
	{"ポーションを手に入れた▼  ",0,0},
};

/* ナイフの入手イベント ２回め以降で持っていなかった時 */
extendstr talk_st3_3_1[] ={
	{"仲間：「懸命な判断だな！ ",0,1},
	{"やっぱりナイフ必要だろ？」  ",8,1},
};

/* ナイフの入手イベント 装備した時 */
extendstr talk_st3_3_2[] ={
	{"仲間：「がんばれよ！」▼ ",0,0},
};

/* ナイフの入手イベント 装備しなかった時 */
extendstr talk_st3_3_3[] ={
	{"仲間：「後悔すんなよ？」▼ ",0,0},
};

/* 中央マップ右 Nasu(予定地) */
extendstr talk_st3_5_1[] ={
	{"村人：「うむうむ。今年もしっかり実ったなぁ」▼ ",0,0},
	{"ナオキ：「茄子畑か？」▼ ",0,0},
	{"村人：「ナオキ様！さようでございます。▼ ",0,1},
	{"私の家系は代々茄子農家をやっておりまして、 ",6,1},
	{"王室にも献上しております。」▼ ",10,0},
	{"ナオキ：「あの美味い茄子はこの畑のものだったのか。 ",0,1},
	{"良いものを作っているんだな。」▼ ",7,0},
	{"村人：「ありがたきお言葉でございます。」▼ ",0,0},
	{"アリストは畑の真ん中で不思議そうに茄子を見ている。▼ ",0,0},
	{"ナオキ：「アリストには馴染みのないものか？」▼ ",0,0},
	{"アリスト：「いえ、オルディンには生えていませんでしたが ",0,1},
	{"書物で読んだことがあります。」▼ ",9,0},
	{"ナオキ：「書物の情報と実物ではそんなに違うか？」▼ ",0,0},
	{"アリスト：「そうではなくて… ",0,1},
	{"この茄子だけ他のものと雰囲気が違うというか…」▼ ",9,0},
	{"ナオキ：「どういうことだ？」▼ ",0,0},
	{"ツヤのある紫色の皮、 ",5,1},
	{"みずみずしい手触り、 ",15,1},
	{"ずっしりと感じる重み。▼ ",25,0},
	{"他の茄子とは一線を画す存在感を放っていた。▼ ",0,0},
};

extendstr talk_st3_5_2[] ={
	{"村人：「おお、お目が高い。▼ ",0,0},
	{"この一つだけはとてもよく育っておりましてな、 ",6,1},
	{"私も生まれて初めて見るほどの出来なのです。 ",6,1},
	{"それもきっと私の先祖も目にしたことがないほどの。」▼ ",6,0},
	{"ナオキ：「ふむ。確かに他の物とは何かが違うのは分かる。▼ ",0,1},
	{"だが…そんなに違うのか？」▼ ",7,0},
	{"ナオキとアリストには違いは分かるが、 ",0,1},
	{"それが他の茄子とどの程度違うのかがわからなかった。▼ ",0,0},
};

extendstr talk_st3_5_3[] ={
	{"村人：「この家で育てられたからでしょうか、感じるのです。 ",0,1},
	{"たとえるならば楽園の禁断の果実、",8,1},
	{"とでも言いましょうか。」▼ ",31,0},
	{"アリスト：「それほどのものが…！」▼ ",0,0},
	{"村人：「ナオキ様、この茄子を差し上げます。 ",0,1},
	{"ぜひお二人でお食べください。」▼ ",6,0},
	{"ナオキ：「いや、ここまで育てたのはお前だろう。▼ ",0,1},
	{"俺たちになんか…」",12,0},
	{"村人：「いやいや、私はこの茄子に気付いてもらえたことが ",0,1},
	{"とてもうれしいのです！ぜひお受け取りください。 ",6,1},
	{"この茄子…いや、ソ\ラナム・メロンゲナを！」▼ ",6,0},
	{"二人：「ソ\ラナム…メロンゲナ…！」▼ ",0,0},
	{"村人：「これを食べれば見える世界は一変し、 ",0,1},
	{"体に力がみなぎり絶大な祝福をもたらすでしょう。」▼ ",6,0},
	{"勢いに負けて茄子…いや、 ",0,1},
	{"ソ\ラナム・メロンゲナを受け取ってしまった。▼ ",0,0},
	{"ナオキ：「あ、ありがとう。美味しくいただくよ。」 ",0,1},
	{"アリスト：「ありがとうございます。」▼ ",0,0},
};

/* 右マップ左 空 */
extendstr talk_st3_6[] ={
	{"なにもない▼  ",0,0},
};

extendstr beforebattle_stage3[] ={
	{"アリスト：「帝國を統べるデジレ＝シニジェには ",0,1},
	{"和平という考えなど初めから存在しない。」▼  ",10,0},
	{"大切なのは想いの純度であり、意思の強さ。▼ ",8,0},
	{"ナオキ：「強い意思を持って、悪辣なる支配者に挑もう」▼ ",0,0},
};

extendstr afterbattle_stage3[] ={
	{"勝者の義務とは貫くことであり、 ",10,1},
	{"何を選ぶかなどそんなことは ",15,1},
	{"総じて馬鹿馬鹿しい概念である。▼ ",20,0},
	{"ナオキ：「王道で行こうぜ、王道で。」 ▼  ",15,0},
};

/* ステージ4 プロローグ */
extendstr cenario_stage4[] ={
	{"『この世界において　 ",0,1},
	{"かつてこれほど人間が幸福だったことがあるだろうか？』▼ ",2,0},
	{"どのようにして幸福がもたらされたかは ",0,1},
	{"誰も知らず、誰も気付かない。▼ ",16,0},
	{"ナオトに何故國にきたのか、 ",0,1},
	{"何故王選に協力したのか、 ",6,1},
	{"地上を統べた後も留まっているのか、 ",10,1},
	{"と尋ねられた▼ ",42,0},
	{"その場では答えられたが、 ",0,1},
	{"考えてみると明確な理由が見つからない ",10,0},
	{"アリスト：「私は何者なのだろう？」▼ ",0,0},
};

extendstr talk_st4_0[] = {
	{"仲間：「頼まれてた弓、完成したぜ」 ",0,1},
	{"ナオキ：「アリストのために頼んでおいたんだ。どうかな」 ",0,1},
	{"アリストに装備しますか？ ",10,1}
};

/* ナイフの入手イベント ２回め以降で持っていなかった時 */
extendstr talk_st4_0_1[] ={
	{"仲間：「頼まれてた弓、まだとってあるぞ」 ",0,1},
	{"ナオキ：「やっぱり弓を持ってたほうが有利じゃないか？」 ",0,1},
	{"アリストに装備しますか？ ",10,1}
};

/* ナイフの入手イベント 装備した時 */
extendstr talk_st4_0_2[] ={
	{"ナオキ：「後ろは頼んだぜ！」▼ ",0,0},
};

/* ナイフの入手イベント 装備しなかった時 */
extendstr talk_st4_0_3[] ={
	{"ナオキ：「大丈夫かなぁ」▼ ",0,0},
};

extendstr talk_st4_1[] = {
	{"仲間：「盾はどうだ？防御は最大の攻撃って言うだろう」▼ ",0,0},
	{"アリスト：「私にはちょうどいい大きさかもしれませんね」 ",0,1},
	{"アリストに装備しますか？ ",10,1},
};

/* ナイフの入手イベント ２回め以降で持っていなかった時 */
extendstr talk_st4_1_1[] ={
	{"仲間：「ほんとに持っていかなくていいのか？」▼ ",0,0},
	{"ナオキ：「盾かぁ…アリスト、どうする？」 ",0,1},
	{"アリストに装備しますか？▼ ",10,1}
};

/* ナイフの入手イベント 装備した時 */
extendstr talk_st4_1_2[] ={
	{"アリスト：「備えあれば憂い無し、ですね」▼ ",0,0},
};

/* ナイフの入手イベント 装備しなかった時 */
extendstr talk_st4_1_3[] ={
	{"ナオキ：「なにが飛んでくるかわからないぞ？」▼ ",0,0},
};

extendstr talk_st4_3[] = {
	{"住民：「. . . なんて言おうとおもったんだっけ」▼ ",0,0},
};

extendstr talk_st4_5[] = {
	{"特に変わったことはない▼ ",0,0},
};

extendstr talk_st4_6[] = {
	{"住民１：「下からきて暴\れてるやつがいるって？」▼ ",0,0},
	{"住民２：「大したことはないだろう。▼ ",0,0},
	{"強力な修復機能\の開発に成功したと聞いているし。▼ ",10,0},
	{"半分以上損傷すると高速で修復できるらしい」▼ ",10,0},
	{"住民１：「そうなのか！行動阻害装置の成果も順調らしいし、 ",0,1},
	{"案外あっさり収まりそうだな」▼ ",10,0},
	{"住民２：「ただ、早々に大きいのをもらっちまうと ",0,1},
	{"間に合わないかもしれない、油断はできないな」▼ ",10,0}
};

extendstr beforebattle_stage4[] = {
	{"アリスト：「ここからどうやって行くの？」▼ ",0,0},
	{"ナオキ：「これに乗って連中の所に行く。」▼ ",0,0},
	{"そう言うとナオキは後ろにあった兵器を指さした▼ ",0,0},
	{"ナオキ：「こいつはかつての大戦の兵器だ ",0,1},
	{"こいつの名前は…」▼ ",16,0},
	{"アリスト：「アルトリー　それが、この子の名前」▼ ",0,0},
	{"ナオキを含むその場にいた人全員が驚いていた▼ ",0,0},
	{"アリストも何故自分に名前が判ったのか判らない▼ ",0,0},
	{"いったい、どうして ",17,1},
	{"私は、貴方の下に来たのだろう？",19,1},
	{"どうして私は、貴方に協力しているのだろう？▼ ",0,0},
};

extendstr afterbattle_stage4_1[] ={
	//メインストーリー戦闘後
	{"アリスト：「やっと、終わった…」 ",0,1},
	{"アリストは肩で息をしながら外の光景を見て安堵していた。▼ ",0,0},
	{"ナオキ：「やったな、アリストこれで國を取り戻せるな。」 ",0,1},
	{"ナオキが言葉を言い終わる前に兵器が崩れていった。▼ ",8,0},
	{"ナオキ：「な、…なんだ！？」　▼ ",14,0},
	{"何が起きたのかもわからぬまま、 ",0,1},
	{"二人と兵器の残骸は遠く地表\へと落ちていった。▼ ",12,0},
};

extendstr afterbattle_stage4_2[] ={
	//画面切り替え
	{"ナオトはお手柄だったと言う訳だな。▼ ",0,0},
	{"彼の言葉がアリストを狂わせた。▼ ",0,0},
	{"何も持たぬが故に、無垢であった少女が ",0,1},
	{"王選でのナオキと国王を見て",0,1},
	{"父を、子という立場を知り ",15,1},
	{"愛情を知る。▼ ",20,0},
	{"実に効果的だよ。　▼ ",18,0},
	{"奪うにはまず与えねばならん。　▼ ",16,0},
	{"お前に認めてもらいたかったのだろう。　▼ ",12,0},
};

extendstr afterbattle_stage4_3[] ={
	//画面切り替え
	{"可愛いな　▼ ",0,0},
	{"私が造ってやっただけはある。▼ ",0,0},
	{"ナオキ：「悪い、最後は守ることできそうにないが、",0,1},
	{"それでも俺を信じてくれるか？」 ",28,1},
	{"ナオキは死ぬかもしれない状況の中で笑っていた。▼ ",0,0},
	{"リーレル（私は貴女と今を生きるために） ",0,0},
	{"自分の騎士の最後の言葉を胸に、アリストは大きく頷く。▼ ",0,0},
	{"ナオキ：「お前の騎士の名を呼べ、アリスト」　▼ ",0,0},
	{"アリスト：「今何よりも幸福なこの瞬間―\ ",0,1},
	{"例え死んだとしても、私は決して忘れない」▼ ",16,0},
};

/* ステージ5 プロローグ */
extendstr cenario_stage5[] ={
	{"アリスト：「来なさい、リーレル」　▼ 　",0,0},
	{"今荘厳な太陽に焼かれ、　",0,1},
	{"蝋の体は融け墜ちた。　▼ ",10,0},
	{"約束された末路にしかし、　",0,1},
	{"嘆きも恐れも私達にはない。　▼ ",14,0},
	{"天に煌めく神話こそ、　 ",0,1},
	{"今も気高き我が光景。　▼ ",10,0},
	{"猛き炎に抱いだかれながら　 ",14,1},
	{"浄化の熱を浴びるのだ　▼ ",20,0},
	{"この墜落に悔いは無し。　▼ ",0,0},
	{"されど今、水底に響く音色は何なのか？　▼ ",0,0},
	{"悲哀を奏でる地上の音。　▼ ",20,0},
	{"かくも心に滲み入いる。　▼ ",24,0},
	{"この悲しみは何なのか、　 ",0,1},
	{"しかし、優しいあの日の思い出は　 ",14,1},
	{"決して嘘ではないのだから　▼ ",22,0},
	{"アリスト：「ナオキ、貴方の力が必要だ」　▼ ",0,0},
	{"ナオキ：「当然ーおまえのすべてが必要だ。」　▼ ",0,0},
};

extendstr afterbattle_stage5[] ={
	{"ナオキ：「共に生きて行こう　 ",0,1},
	{"天も地も関係ない。　▼ ",12,0},
	{"アリストとなら　 ",14,1},
	{"何処へでも行ける。」　▼　 ",17,0},
};


# 選択じゃんけん

プロジェクトの clone から実行までの流れは [実行手順](#exec) 参照。

## 概要

### 使用言語

c/c++
[dxLib](https://dxlib.xsrv.jp/)使用

### 制作期間

11 日

## ゲームの流れ

シンジくん VS コンピュータ (仮称:使徒)

1. じゃんけんの出し手を二つ選ぶ。
   (ここで選んだ手は変えることはできない)
   (同じ手を二つ選んでもよい)
   仮に、シンジはグーとチョキ
   使徒はグーとパー を選んだとする。
2. シンジと使徒は同時に一方の手を相手に見せる
   仮に、 シンジはチョキ
   使徒はパー を見せたとする
3. 相手の出した一方の手を確認した後、 自分の勝負する手を決める
4. シンジ=チョキ、 使徒=グーを出した場合は使徒の勝ち

## 作った経緯

元々、 実家で家事をする人を決める際に行っていたゲームで、
c/c++ を使用した制作物を作るにあたり、 ちょうどいい難易度だと思い制作。

## こだわり

- 画面をシンプルにし、 直感的な操作を実現
  じゃんけんとはいえ、 ルールが複雑なので、 最小限のボタンかつ、
  端的な説明をつけ操作に対して悩むことのない UI とした。
- 飽きないように、ハードモードを追加
  ゲームとしての UX を高めるために、 通常モードだけでなくハードモードを組み込むことで、勝てた時の喜びをより感じるように設計。

<a id="exec"></a>

## 実行手順

前準備
[ＤＸライブラリのダウンロード](https://dxlib.xsrv.jp/dxdload.html)から VisualStudio(c++)用をダウンロード

1. clone
2. ダウンロードファイルを展開し C:/ へ移動
   ([公式ページ](https://dxlib.xsrv.jp/use/dxuse_vscom2022.html)の 4-6 と同様)
3. visual studio 2022 にてプロジェクトファイルを開く
4. 実行してアプリが開けば終了
WinKiosk by 片山博文MZ
----------------------

WinKiosk は、Windows用の無料の情報キオスク端末システムです。
Windows Vista/7/10で動作します。

☆ 構成

WinKiosk は、SimpleBrowser と KeybdSystem からなります。
SimpleBrowser はWebブラウザです。
KeybdSystem は、仮想キーボードのシステムです。

WinKiosk は、SimpleBrowser をキオスクモードで起動します。
SimpleBrowser 上で、「キーボード」ボタンを押せば、KeybdSystem を起動できます。

☆ ショートカット キー

SimpleBrowser では、Ctrl+K を押せばキオスクモードの ON/OFF を切り替えることができます。
SimpleBrowser では、Alt+F4 を押せば SimpleBrowser を終了できます。
SimpleBrowser では、Alt+F を押せばメニューを表示できます。

Alt+F4 と Ctrl+K と Alt+F は覚えておいて下さい。

| キーの組み合わせ | コマンド                   |
|------------------|----------------------------|
| Ctrl+R           | 再読み込み                 |
| F5               | 再読み込み                 |
| Alt+Left         | １つ戻る                   |
| Alt+Right        | １つ進む                   |
| Alt+Home         | ホームへ移動               |
| Esc              | 停止                       |
| Alt+D            | アドレスバーへ移動         |
| Ctrl+P           | 印刷...                    |
| Shift+Ctrl+P     | 印刷!                      |
| Ctrl+U           | ソースを見る               |
| Alt+F            | 点々メニューを表示         |
| Ctrl+N           | 新しいウィンドウ           |
| Ctrl+K           | キオスクモードを切り替える |
| Alt+F4           | SimpleBrowserを終了する    |

☆ 初期設定

Windows 10の場合は、OSのアクティブ時間を設定して下さい。

スタートアップに登録しておけば、Windowsを再起動すると、自動的に WinKiosk が起動されます。
スタートアップに登録またはスタートアップから削除するには、setupper.exeをお使い下さい。

SimpleBrowser のボタンは

    Upside_ja.txt
    Downside_ja.txt
    LeftSide_ja.txt
    RightSide_ja.txt

をメモ帳などで変更して SimpleBrowser を再読み込みすることにより、カスタマイズ可能です (タブ区切りのテキスト)。
コマンドID (ID_*) は、resource.hで定義されています。

☆ セキュリティ

情報キオスク端末として利用したいのであれば、必要ないプリンタは
削除した方がいいかもしれません。

キオスクモードでは、点々メニュー ("...") と印刷プレビューは
セキュリティ上の理由から利用できません。

情報キオスク端末として利用を開始する場合は、物理キーボードの
接続を断って下さい。

hw1：
撰寫一程式，使用方式如下：
./sed  [ -g(optional) ]  [ -source(required) ]  [ -target(required) ]
程式從標準輸入逐行讀入，將每行第一個出現 [ -source ] 字串的地方取代為 [ -target ] 字串。
若 [ -g ] 被啟用，則將每行所有出現  [ -source ] 字串的地方取代為 [ -target ] 字串。
[ -source ] 與 [ -target ] 長度介於 1 ~ 256 之間，且每行不超過 1024 個 byte。
將取代結果於標準輸出印出。
輸入及輸出每行皆以換行符號( '\n' ) 結尾。
若輸入的參數有 2 個，參數依序為 [ -source ] 與 [ -target ]，
若輸入的參數有 3 個，參數依序為 [ -g ]、[ -source ] 與 [ -target ]，
任何未定義的操作需印出 help message，詳細請參考範例輸出。

hw2：
請完成一通訊錄程式可以記錄  姓名 、 email 、 網頁連結 及 手機號碼  並包含以下功能:

創建通訊錄
根據程式參數 argv[1]，新建 N 個聯絡人的通訊錄
N 筆輸入，格式為  <name>\t<email>\t<url>\t<phone_number> 
創建完後進入指令模式

新增聯絡人 (i)
格式: i\t<name>\t<email>\t<url>\t<phone_number> 
功能: 在通訊錄最後一筆後面插入新的聯絡人，資料中間以 \t 隔開，資料不會有空值。
ex: i jack jack@email.example hello.world.tw 987654321 (新增 jack 聯絡人)
更新聯絡人 (u)
格式: u\t<name>\t<email>\t<url>\t<phone_number> 

功能: 更新既有聯絡人資訊，資料中間以 \t 隔開，資料不會有空值。
ex: u jack jack123@email.email hello.world.tw 123456789(更新 jack 聯絡人資訊)
刪除聯絡人 (d)
格式: d\t<name> 
功能: 刪除特定聯絡人
ex: d jack (刪除 jack)
找尋 (f)
格式: f\t<pattern> 
功能: 找尋有 <pattern> 的聯絡人，<pattern> 有分大小寫。
		  若有找到符合的聯絡人，則輸出聯絡人資訊；沒有則需輸出沒有結果 (見範例輸出)
ex: f jack(找尋 jack 以及名字裡含 jack 的聯絡人，例如: jack, jack_son, man_jack等等 ) 
排序 (s)
格式: s\t<pattern> 
功能: 以 <pattern> 欄位從小到大排序 (僅排序，不須輸出)。
		 欄位分為 n (姓名) 、 e (email) 、 u (網址) 、 p (手機號碼)
		 手機號碼以數值排序 (可使用  atoi() )，其餘以 ASCII 碼值做比較
ex: s n(將通訊錄以名字從小到大排序)
顯示通訊錄內容 (p)
格式: p 
功能: 以特定格式輸出通訊錄
離開程式 (q, quit)
格式: q 、 quit 
功能: 結束程式

hw6：
撰寫一程式，使用 Binary Search Tree (BST) 進行單詞統計，每個節點儲存單字及單字數量。
BST 須符合每個節點中左子樹所有節點字串小於該節點字串，右子樹所有節點字串大於該節點字串。
程式流程
如果輸入之單字為單字則插入 BST ，若已在 BST 裡則新增或減少單字數量。
使用 inorder traversal 方式輸出 BST 的內容。
將 BST 轉成 array 後，進行排序。
比較方式為單字數量大的在前面，小的在後面
數量一樣則以字串 ASCII 碼較小的在前面。
輸出排序後內容


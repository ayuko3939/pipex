# pipex

42Tokyoのpipexプロジェクト - Unixのパイプ機能を再実装する課題です。

## 概要

pipexは、シェルのパイプ（`|`）機能を模倣するプログラムです。2つのコマンドを連結し、最初のコマンドの出力を2番目のコマンドの入力として渡します。

### 基本動作
```bash
# 通常のシェルでの動作
< file1 cmd1 | cmd2 > file2

# pipexでの動作
./pipex file1 cmd1 cmd2 file2
```

## コンパイル

### 必須部分
```bash
make
```

### ボーナス部分
```bash
make bonus
```

### クリーンアップ
```bash
make clean    # オブジェクトファイルを削除
make fclean   # 実行ファイルも含めて削除
make re       # 再コンパイル
```

## 使用方法

### 必須部分
```bash
./pipex infile cmd1 cmd2 outfile
```

**例:**
```bash
./pipex input.txt "ls -l" "wc -l" output.txt
# 以下と同等: < input.txt ls -l | wc -l > output.txt
```

### ボーナス部分

#### 複数パイプ
```bash
./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile
```

#### Here_doc機能
```bash
./pipex here_doc LIMITER cmd1 cmd2 outfile
```

**例:**
```bash
./pipex here_doc END "grep hello" "wc -l" output.txt
# 以下と同等: cmd1 << END | cmd2 > output.txt
```

## ファイル構成

### 必須部分
- `mandatory/pipex.c` - メイン処理
- `mandatory/pipex_utils.c` - ユーティリティ関数
- `mandatory/parse.c` - パス解析・コマンド処理
- `mandatory/pipex.h` - ヘッダーファイル

### ボーナス部分
- `bonus/pipex_bonus.c` - ボーナス機能のメイン処理
- `bonus/pipex_utils.c` - ユーティリティ関数
- `bonus/parse.c` - パス解析・コマンド処理
- `bonus/data_manage.c` - データ管理
- `bonus/here_doc.c` - Here_doc機能
- `bonus/pipex_bonus.h` - ボーナス用ヘッダーファイル

### 依存ライブラリ
- `libft/` - 42Tokyoの標準ライブラリ
- `get_next_line/` - ファイル読み込み用（ボーナスで使用）

## 実装された機能

### 必須部分
- ✅ 基本的なパイプ機能（2つのコマンド）
- ✅ ファイル入出力
- ✅ エラーハンドリング
- ✅ 環境変数PATHからのコマンド検索
- ✅ 相対パス・絶対パスでのコマンド実行

### ボーナス部分
- ✅ 複数パイプ処理
- ✅ Here_doc機能（`<<`オペレーター）
- ✅ 拡張エラーハンドリング

## エラーハンドリング

- ファイルが開けない場合の適切なエラーメッセージ
- コマンドが見つからない場合の処理
- 権限エラーの処理
- メモリ不足の処理

## 注意事項

- メモリリークを防ぐため、すべての動的メモリは適切に解放されます
- Address Sanitizerを使用してメモリエラーをチェックしています（`-fsanitize=address`）
- シェルと同様のエラーコードを返します

## テスト例

```bash
# 基本テスト
./pipex input.txt "cat" "wc -l" output.txt

# 複数パイプ（ボーナス）
./pipex input.txt "cat" "grep hello" "wc -l" output.txt

# Here_doc（ボーナス）
./pipex here_doc EOF "cat" "wc -l" output.txt
```

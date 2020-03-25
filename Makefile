menu: AI2.cpp count2.cpp end_game2.cpp initiate_board2.cpp judge_end2.cpp legal_moves2.cpp main2.cpp players_turn2.cpp print_board2.cpp read_from_file2.cpp reverse2.cpp save_to_file2.cpp
	g++ -o menu AI2.cpp count2.cpp end_game2.cpp initiate_board2.cpp judge_end2.cpp legal_moves2.cpp main2.cpp players_turn2.cpp print_board2.cpp read_from_file2.cpp reverse2.cpp save_to_file2.cpp
players_turn2.cpp: players_turn.cpp
	iconv -f gb2312 -t utf-8 players_turn.cpp > players_turn2.cpp
AI2.cpp: AI.cpp
	iconv -f gb2312 -t utf-8 AI.cpp > AI2.cpp
count2.cpp: count.cpp
	iconv -f gb2312 -t utf-8 count.cpp > count2.cpp
end_game2.cpp: end_game.cpp
	iconv -f gb2312 -t utf-8 end_game.cpp > end_game2.cpp
initiate_board2.cpp: initiate_board.cpp
	iconv -f gb2312 -t utf-8 initiate_board.cpp > initiate_board2.cpp
judge_end2.cpp: judge_end.cpp
	iconv -f gb2312 -t utf-8 judge_end.cpp > judge_end2.cpp
legal_moves2.cpp: legal_moves.cpp
	iconv -f gb2312 -t utf-8 legal_moves.cpp > legal_moves2.cpp
main2.cpp: main.cpp
	iconv -f gb2312 -t utf-8 main.cpp > main2.cpp
read_from_file2.cpp: read_from_file.cpp
	iconv -f gb2312 -t utf-8 read_from_file.cpp > read_from_file2.cpp
reverse2.cpp: reverse.cpp
	iconv -f gb2312 -t utf-8 reverse.cpp > reverse2.cpp
save_to_file2.cpp: save_to_file.cpp
	iconv -f gb2312 -t utf-8 save_to_file.cpp > save_to_file2.cpp
print_board2.cpp: print_board.cpp
	iconv -f gb2312 -t utf-8 print_board.cpp > print_board2.cpp

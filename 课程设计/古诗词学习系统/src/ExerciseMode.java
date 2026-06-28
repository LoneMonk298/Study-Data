import java.util.*;

public class ExerciseMode {
    private PoemSystem system;
    private Scanner scanner;
    private static final int DEFAULT_QUESTION_COUNT = 10;
    private static final int DEFAULT_SCORE_PER_QUESTION = 10;

    public ExerciseMode(PoemSystem system) {
        this.system = system;
        this.scanner = new Scanner(System.in);
    }

    // 启动练习模式
    public void start() {
        boolean exit = false;
        
        while (!exit) {
            showMenu();
            int choice = getChoice();
            
            switch (choice) {
                case 1:
                    startTitlePoetExercise();
                    break;
                case 2:
                    startSentenceExercise();
                    break;
                case 3:
                    showExerciseHistory();
                    break;
                case 0:
                    exit = true;
                    System.out.println("退出练习模式...");
                    break;
                default:
                    System.out.println("无效的选择，请重新输入！");
            }
        }
    }

    // 显示练习模式菜单
    private void showMenu() {
        System.out.println("\n===== 练习模式 =====");
        System.out.println("1. 古诗标题诗人练习（显示诗句，填写标题和诗人）");
        System.out.println("2. 诗句填空练习（显示标题和部分诗句，填写其他诗句）");
        System.out.println("3. 查看练习历史");
        System.out.println("0. 退出练习模式");
        System.out.print("请选择功能：");
    }

    // 获取用户选择
    private int getChoice() {
        int choice = -1;
        try {
            choice = scanner.nextInt();
            scanner.nextLine(); // 消耗换行符
        } catch (Exception e) {
            scanner.nextLine(); // 清除输入缓冲区
        }
        return choice;
    }

    // 启动标题诗人练习
    private void startTitlePoetExercise() {
        List<Poem> masteredPoems = system.getMasteredPoems();
        
        if (masteredPoems.isEmpty()) {
            System.out.println("\n您还没有掌握任何古诗！请先在学习模式中添加已掌握的古诗。");
            return;
        }
        
        System.out.print("\n请输入要练习的题目数量（默认为" + DEFAULT_QUESTION_COUNT + "题）：");
        int questionCount = getQuestionCount();
        
        // 确保题目数量不超过已掌握古诗的数量
        questionCount = Math.min(questionCount, masteredPoems.size());
        
        System.out.println("\n===== 古诗标题诗人练习 =====");
        System.out.println("（请根据显示的诗句，填写正确的古诗标题和诗人）");
        
        int correctCount = 0;
        List<String> details = new ArrayList<>();
        
        // 创建随机抽取的古诗列表，避免重复
        List<Poem> selectedPoems = new ArrayList<>(masteredPoems);
        Collections.shuffle(selectedPoems);
        selectedPoems = selectedPoems.subList(0, questionCount);
        
        for (int i = 0; i < questionCount; i++) {
            Poem poem = selectedPoems.get(i);
            System.out.println("\n--- 第 " + (i + 1) + " 题 ---");
            
            // 显示诗句
            System.out.println("诗句：");
            for (String line : poem.getLines()) {
                System.out.println(line);
            }
            
            // 输入标题
            System.out.print("请输入古诗标题：");
            String titleAnswer = scanner.nextLine().trim();
            
            // 输入诗人
            System.out.print("请输入诗人姓名：");
            String poetAnswer = scanner.nextLine().trim();
            
            // 判断答案是否正确
            boolean titleCorrect = titleAnswer.equals(poem.getTitle());
            boolean poetCorrect = poetAnswer.equals(poem.getPoet().getName());
            
            // 显示正确答案
            System.out.println("\n正确答案：");
            System.out.println("标题：" + poem.getTitle());
            System.out.println("诗人：" + poem.getPoet().getName());
            
            // 记录结果
            if (titleCorrect && poetCorrect) {
                System.out.println("答案正确！");
                correctCount++;
                details.add("第" + (i + 1) + "题：正确 - 《" + poem.getTitle() + "》");
            } else {
                System.out.println("答案错误！");
                details.add("第" + (i + 1) + "题：错误 - 《" + poem.getTitle() + "》");
            }
        }
        
        // 计算得分
        int score = (correctCount * DEFAULT_SCORE_PER_QUESTION * DEFAULT_QUESTION_COUNT) / questionCount;
        
        // 显示成绩
        showResult(questionCount, correctCount, score);
        
        // 保存练习结果
        ExerciseResult result = new ExerciseResult(questionCount, correctCount, score);
        for (String detail : details) {
            result.addDetail(detail);
        }
        system.addExerciseResult(result);
    }

    // 启动诗句填空练习
    private void startSentenceExercise() {
        List<Poem> masteredPoems = system.getMasteredPoems();
        
        // 筛选至少有4句的古诗（用于前两句填后两句或后两句填前两句）
        List<Poem> eligiblePoems = new ArrayList<>();
        for (Poem poem : masteredPoems) {
            if (poem.getLines().size() >= 4) {
                eligiblePoems.add(poem);
            }
        }
        
        if (eligiblePoems.isEmpty()) {
            System.out.println("\n您的已掌握古诗中没有足够长的诗句用于此练习！请先在学习模式中添加更多已掌握的古诗。");
            return;
        }
        
        System.out.print("\n请输入要练习的题目数量（默认为" + DEFAULT_QUESTION_COUNT + "题）：");
        int questionCount = getQuestionCount();
        
        // 确保题目数量不超过符合条件的古诗数量
        questionCount = Math.min(questionCount, eligiblePoems.size());
        
        System.out.println("\n===== 诗句填空练习 =====");
        System.out.println("（请根据显示的标题和部分诗句，填写其他诗句）");
        
        int correctCount = 0;
        List<String> details = new ArrayList<>();
        
        // 创建随机抽取的古诗列表，避免重复
        List<Poem> selectedPoems = new ArrayList<>(eligiblePoems);
        Collections.shuffle(selectedPoems);
        selectedPoems = selectedPoems.subList(0, questionCount);
        
        for (int i = 0; i < questionCount; i++) {
            Poem poem = selectedPoems.get(i);
            System.out.println("\n--- 第 " + (i + 1) + " 题 ---");
            
            // 显示标题
            System.out.println("古诗：《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
            
            // 随机决定是显示前两句填后两句，还是显示后两句填前两句
            Random random = new Random();
            boolean showFirstTwo = random.nextBoolean();
            
            if (showFirstTwo) {
                // 显示前两句
                System.out.println("前两句：");
                List<String> firstTwoLines = poem.getFirstTwoLines();
                for (String line : firstTwoLines) {
                    System.out.println(line);
                }
                
                // 输入后两句
                System.out.println("请输入后两句诗句（每行一句）：");
                List<String> lastTwoLines = poem.getLastTwoLines();
                boolean allCorrect = true;
                
                for (int j = 0; j < lastTwoLines.size(); j++) {
                    System.out.print("第" + (j + 3) + "句：");
                    String answer = scanner.nextLine().trim();
                    if (!answer.equals(lastTwoLines.get(j))) {
                        allCorrect = false;
                    }
                }
                
                // 显示正确答案
                System.out.println("\n正确答案：");
                for (int j = 0; j < lastTwoLines.size(); j++) {
                    System.out.println("第" + (j + 3) + "句：" + lastTwoLines.get(j));
                }
                
                // 记录结果
                if (allCorrect) {
                    System.out.println("答案正确！");
                    correctCount++;
                    details.add("第" + (i + 1) + "题：正确 - 《" + poem.getTitle() + "》（后两句）");
                } else {
                    System.out.println("答案有误！");
                    details.add("第" + (i + 1) + "题：错误 - 《" + poem.getTitle() + "》（后两句）");
                }
            } else {
                // 显示后两句
                System.out.println("后两句：");
                List<String> lastTwoLines = poem.getLastTwoLines();
                for (String line : lastTwoLines) {
                    System.out.println(line);
                }
                
                // 输入前两句
                System.out.println("请输入前两句诗句（每行一句）：");
                List<String> firstTwoLines = poem.getFirstTwoLines();
                boolean allCorrect = true;
                
                for (int j = 0; j < firstTwoLines.size(); j++) {
                    System.out.print("第" + (j + 1) + "句：");
                    String answer = scanner.nextLine().trim();
                    if (!answer.equals(firstTwoLines.get(j))) {
                        allCorrect = false;
                    }
                }
                
                // 显示正确答案
                System.out.println("\n正确答案：");
                for (int j = 0; j < firstTwoLines.size(); j++) {
                    System.out.println("第" + (j + 1) + "句：" + firstTwoLines.get(j));
                }
                
                // 记录结果
                if (allCorrect) {
                    System.out.println("答案正确！");
                    correctCount++;
                    details.add("第" + (i + 1) + "题：正确 - 《" + poem.getTitle() + "》（前两句）");
                } else {
                    System.out.println("答案有误！");
                    details.add("第" + (i + 1) + "题：错误 - 《" + poem.getTitle() + "》（前两句）");
                }
            }
        }
        
        // 计算得分
        int score = (correctCount * DEFAULT_SCORE_PER_QUESTION * DEFAULT_QUESTION_COUNT) / questionCount;
        
        // 显示成绩
        showResult(questionCount, correctCount, score);
        
        // 保存练习结果
        ExerciseResult result = new ExerciseResult(questionCount, correctCount, score);
        for (String detail : details) {
            result.addDetail(detail);
        }
        system.addExerciseResult(result);
    }

    // 显示练习历史
    private void showExerciseHistory() {
        List<ExerciseResult> results = system.getStudyRecord().getExerciseResults();
        
        if (results.isEmpty()) {
            System.out.println("\n您还没有进行过练习！");
            return;
        }
        
        System.out.println("\n===== 练习历史 =====");
        System.out.println("共进行了 " + results.size() + " 次练习");
        System.out.println("平均成绩：" + String.format("%.1f", system.getStudyRecord().getAverageScore()) + "分");
        
        // 显示最近的5次练习记录
        System.out.println("\n最近的练习记录：");
        List<ExerciseResult> recentResults = system.getStudyRecord().getRecentExerciseResults(5);
        
        for (int i = 0; i < recentResults.size(); i++) {
            ExerciseResult result = recentResults.get(i);
            System.out.println((i + 1) + ". " + result);
        }
        
        // 询问是否查看某次练习的详细记录
        System.out.print("\n请输入要查看详细记录的练习序号（0返回）：");
        int index = getChoice();
        
        if (index > 0 && index <= recentResults.size()) {
            ExerciseResult selectedResult = recentResults.get(index - 1);
            System.out.println("\n详细记录：");
            for (String detail : selectedResult.getDetails()) {
                System.out.println(detail);
            }
        }
    }

    // 获取用户输入的题目数量
    private int getQuestionCount() {
        int count = DEFAULT_QUESTION_COUNT;
        String input = scanner.nextLine().trim();
        
        if (!input.isEmpty()) {
            try {
                count = Integer.parseInt(input);
                if (count <= 0) {
                    count = DEFAULT_QUESTION_COUNT;
                }
            } catch (NumberFormatException e) {
                // 使用默认值
            }
        }
        
        return count;
    }

    // 显示练习结果
    private void showResult(int totalQuestions, int correctCount, int score) {
        System.out.println("\n===== 练习结果 =====");
        System.out.println("总题目数：" + totalQuestions);
        System.out.println("正确题数：" + correctCount);
        System.out.println("错误题数：" + (totalQuestions - correctCount));
        System.out.println("得分：" + score + "分");
        
        // 给出评价
        double correctRate = (double) correctCount / totalQuestions;
        if (correctRate >= 0.9) {
            System.out.println("评价：太棒了！您对古诗掌握得非常好！");
        } else if (correctRate >= 0.7) {
            System.out.println("评价：不错！继续努力！");
        } else if (correctRate >= 0.5) {
            System.out.println("评价：还可以，需要加强练习！");
        } else {
            System.out.println("评价：加油！建议多复习已掌握的古诗！");
        }
    }

    // 关闭Scanner
    public void close() {
        if (scanner != null) {
            scanner.close();
        }
    }
}
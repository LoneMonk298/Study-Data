import java.util.List;
import java.util.Scanner;

public class StudyMode {
    private PoemSystem system;
    private Scanner scanner;

    public StudyMode(PoemSystem system) {
        this.system = system;
        this.scanner = new Scanner(System.in);
    }

    // 启动学习模式
    public void start() {
        boolean exit = false;
        
        while (!exit) {
            showMenu();
            int choice = getChoice();
            
            switch (choice) {
                case 1:
                    searchPoemByTitle();
                    break;
                case 2:
                    searchPoemsByPoet();
                    break;
                case 3:
                    showMasteredPoems();
                    break;
                case 0:
                    exit = true;
                    System.out.println("退出学习模式...");
                    break;
                default:
                    System.out.println("无效的选择，请重新输入！");
            }
        }
    }

    // 显示学习模式菜单
    private void showMenu() {
        System.out.println("\n===== 学习模式 =====");
        System.out.println("1. 查询古诗（按标题）");
        System.out.println("2. 查询诗人（显示该诗人的所有古诗）");
        System.out.println("3. 查看已掌握的古诗");
        System.out.println("0. 退出学习模式");
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

    // 查询古诗（按标题）
    private void searchPoemByTitle() {
        System.out.print("请输入古诗标题：");
        String title = scanner.nextLine();
        
        Poem poem = system.findPoemByTitle(title);
        
        if (poem != null) {
            System.out.println("\n找到了古诗：");
            System.out.println(poem);
            
            // 询问是否添加到已掌握列表
            askToAddToMastered(poem);
        } else {
            System.out.println("未找到标题为 \"" + title + "\" 的古诗！");
            // 提示可能的相似标题
            suggestSimilarTitles(title);
        }
    }

    // 查询诗人（显示该诗人的所有古诗）
    private void searchPoemsByPoet() {
        System.out.print("请输入诗人姓名：");
        String poetName = scanner.nextLine();
        
        List<Poem> poems = system.findPoemsByPoet(poetName);
        
        if (!poems.isEmpty()) {
            System.out.println("\n找到了 " + poetName + " 的 " + poems.size() + " 首古诗：");
            
            // 显示古诗列表
            for (int i = 0; i < poems.size(); i++) {
                System.out.println((i + 1) + ". 《" + poems.get(i).getTitle() + "》");
            }
            
            // 询问是否查看某首具体的古诗
            System.out.print("\n请输入要查看的古诗序号（0返回）：");
            int index = getChoice();
            
            if (index > 0 && index <= poems.size()) {
                Poem selectedPoem = poems.get(index - 1);
                System.out.println("\n" + selectedPoem);
                
                // 询问是否添加到已掌握列表
                askToAddToMastered(selectedPoem);
            }
        } else {
            System.out.println("未找到诗人 \"" + poetName + "\" 的古诗！");
            // 提示可能的相似诗人名
            suggestSimilarPoets(poetName);
        }
    }

    // 显示已掌握的古诗
    private void showMasteredPoems() {
        List<Poem> masteredPoems = system.getMasteredPoems();
        
        if (!masteredPoems.isEmpty()) {
            System.out.println("\n已掌握的古诗（共" + masteredPoems.size() + "首）：");
            
            for (int i = 0; i < masteredPoems.size(); i++) {
                Poem poem = masteredPoems.get(i);
                System.out.println((i + 1) + ". 《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
            }
            
            // 询问是否查看某首具体的古诗或移除某首古诗
            System.out.print("\n请输入要查看的古诗序号（0返回，负数表示移除）：");
            int index = getChoice();
            
            if (index > 0 && index <= masteredPoems.size()) {
                System.out.println("\n" + masteredPoems.get(index - 1));
            } else if (index < 0 && Math.abs(index) <= masteredPoems.size()) {
                Poem poemToRemove = masteredPoems.get(Math.abs(index) - 1);
                system.removeFromMastered(poemToRemove);
                System.out.println("已将《" + poemToRemove.getTitle() + "》从已掌握列表中移除！");
            }
        } else {
            System.out.println("\n您还没有掌握任何古诗！");
            System.out.println("请在查询古诗后将其添加到已掌握列表。");
        }
    }

    // 询问是否将古诗添加到已掌握列表
    private void askToAddToMastered(Poem poem) {
        boolean alreadyMastered = system.isPoemMastered(poem);
        
        if (alreadyMastered) {
            System.out.println("该古诗已经在您的已掌握列表中！");
        } else {
            System.out.print("是否将此古诗添加到已掌握列表？(y/n)：");
            String answer = scanner.nextLine();
            
            if (answer.equalsIgnoreCase("y")) {
                system.addToMastered(poem);
                System.out.println("已将《" + poem.getTitle() + "》添加到已掌握列表！");
            }
        }
    }

    // 提示可能的相似标题
    private void suggestSimilarTitles(String title) {
        System.out.println("\n可能的相似标题：");
        boolean found = false;
        
        for (Poem poem : system.getAllPoems()) {
            if (poem.getTitle().contains(title) || poem.getTitle().toLowerCase().contains(title.toLowerCase())) {
                System.out.println("- " + poem.getTitle());
                found = true;
            }
        }
        
        if (!found) {
            System.out.println("未找到相似标题的古诗。");
        }
    }

    // 提示可能的相似诗人名
    private void suggestSimilarPoets(String poetName) {
        System.out.println("\n可能的相似诗人：");
        boolean found = false;
        
        for (Poet poet : system.getAllPoets()) {
            if (poet.getName().contains(poetName) || poet.getName().toLowerCase().contains(poetName.toLowerCase())) {
                System.out.println("- " + poet.getName());
                found = true;
            }
        }
        
        if (!found) {
            System.out.println("未找到相似名字的诗人。");
        }
    }

    // 关闭Scanner
    public void close() {
        if (scanner != null) {
            scanner.close();
        }
    }
}
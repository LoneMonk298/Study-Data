public class FileReaderTest {
    public static void main(String[] args) {
        System.out.println("开始测试古诗文件读取功能...");
        
        PoemSystem system = new PoemSystem();
        int poemCount = system.loadPoemsFromFile("d:\\古诗学习系统\\poems.txt");
        
        if (poemCount > 0) {
            System.out.println("\n文件读取成功！");
            System.out.println("\n加载的古诗数量：" + system.getAllPoems().size());
            System.out.println("加载的诗人数量：" + system.getAllPoets().size());
            
            System.out.println("\n古诗列表：");
            for (Poem poem : system.getAllPoems()) {
                System.out.println("- 《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
            }
            
            // 测试查找功能
            System.out.println("\n测试查找功能：");
            Poem poem = system.findPoemByTitle("春晓");
            if (poem != null) {
                System.out.println("\n找到古诗：");
                System.out.println(poem);
            }
            
            System.out.println("\n测试按诗人查找：");
            java.util.List<Poem> liBaiPoems = system.findPoemsByPoet("李白");
            System.out.println("李白的古诗数量：" + liBaiPoems.size());
            for (Poem p : liBaiPoems) {
                System.out.println("- 《" + p.getTitle() + "》");
            }
        } else {
            System.out.println("文件读取失败！");
        }
    }
}
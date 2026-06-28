import java.util.*;
import java.io.*;

public class PoemSystem {
    private Map<String, Poem> poems;          // 所有古诗，标题作为键
    private Map<String, List<Poem>> poetPoems; // 诗人的古诗列表
    private Map<String, Poet> poets;          // 所有诗人
    private StudyRecord studyRecord;          // 学习记录
    private static final String DATA_FILE = "d:\\古诗学习系统\\poems.txt";
    private static final String RECORD_FILE = "d:\\古诗学习系统\\study_record.dat";

    public PoemSystem() {
        this.poems = new HashMap<>();
        this.poetPoems = new HashMap<>();
        this.poets = new HashMap<>();
        this.studyRecord = new StudyRecord();
    }

    // 添加古诗
    public void addPoem(Poem poem) {
        poems.put(poem.getTitle(), poem);
        
        // 添加到诗人的古诗列表
        String poetName = poem.getPoet().getName();
        if (!poetPoems.containsKey(poetName)) {
            poetPoems.put(poetName, new ArrayList<>());
        }
        poetPoems.get(poetName).add(poem);
        
        // 添加诗人（如果不存在）
        if (!poets.containsKey(poetName)) {
            poets.put(poetName, poem.getPoet());
        }
    }

    // 通过标题查找古诗
    public Poem findPoemByTitle(String title) {
        return poems.get(title);
    }

    // 通过诗人名查找古诗列表
    public List<Poem> findPoemsByPoet(String poetName) {
        return poetPoems.getOrDefault(poetName, new ArrayList<>());
    }

    // 获取诗人信息
    public Poet getPoet(String name) {
        return poets.get(name);
    }

    // 添加已掌握的古诗
    public void addToMastered(Poem poem) {
        studyRecord.addMasteredPoem(poem);
    }
    
    // 添加已掌握的古诗（别名方法，兼容不同的调用方式）
    public void addToMasteredPoems(Poem poem) {
        addToMastered(poem);
    }

    // 移除已掌握的古诗
    public void removeFromMastered(Poem poem) {
        studyRecord.removeMasteredPoem(poem);
    }

    // 检查古诗是否已掌握
    public boolean isPoemMastered(Poem poem) {
        return studyRecord.isPoemMastered(poem);
    }

    // 获取已掌握的古诗列表
    public List<Poem> getMasteredPoems() {
        return studyRecord.getMasteredPoems();
    }

    // 添加练习结果
    public void addExerciseResult(ExerciseResult result) {
        studyRecord.addExerciseResult(result);
    }

    // 获取学习记录
    public StudyRecord getStudyRecord() {
        return studyRecord;
    }

    // 获取所有古诗
    public Collection<Poem> getAllPoems() {
        return poems.values();
    }

    // 获取所有诗人
    public Collection<Poet> getAllPoets() {
        return poets.values();
    }

    // 随机获取一首已掌握的古诗（用于练习）
    public Poem getRandomMasteredPoem() {
        List<Poem> masteredPoems = studyRecord.getMasteredPoems();
        if (masteredPoems.isEmpty()) {
            return null;
        }
        Random random = new Random();
        return masteredPoems.get(random.nextInt(masteredPoems.size()));
    }

    // 保存学习记录到文件
    public boolean saveStudyRecord() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(RECORD_FILE))) {
            oos.writeObject(studyRecord);
            return true;
        } catch (IOException e) {
            System.err.println("保存学习记录失败：" + e.getMessage());
            return false;
        }
    }

    // 从文件加载学习记录
    public boolean loadStudyRecord() {
        File file = new File(RECORD_FILE);
        if (!file.exists()) {
            return false;
        }
        
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(RECORD_FILE))) {
            studyRecord = (StudyRecord) ois.readObject();
            return true;
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("加载学习记录失败：" + e.getMessage());
            return false;
        }
    }

    // 从文件加载古诗数据
    public int loadPoemsFromFile(String filePath) {
        // 确保文件存在
        java.io.File file = new java.io.File(filePath);
        if (!file.exists() || !file.isFile()) {
            System.err.println("古诗文件不存在：" + filePath);
            return 0;
        }

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            String title = "";
            String poetName = "";
            String dynasty = "未知";
            List<String> contentLines = new ArrayList<>();
            boolean isReadingContent = false;
            int poemCount = 0;

            while ((line = reader.readLine()) != null) {
                line = line.trim();
                
                // 如果当前没有在读取内容，并且遇到了非空行，检查是否是新的诗
                if (!isReadingContent && !line.isEmpty()) {
                    // 检查是否符合 标题 - 作者(朝代) 的格式
                    if (line.contains("-")) {
                        // 如果之前有保存的诗，先添加它
                        if (!title.isEmpty() && !contentLines.isEmpty()) {
                            createAndAddPoem(title, poetName, dynasty, contentLines);
                            poemCount++;
                            contentLines.clear();
                        }

                        // 解析新的诗信息
                        int separatorIndex = line.indexOf("-");
                        title = line.substring(0, separatorIndex).trim();
                        
                        // 解析作者和朝代
                        String authorPart = line.substring(separatorIndex + 1).trim();
                        if (authorPart.contains("(")) {
                            int leftParen = authorPart.indexOf("(");
                            int rightParen = authorPart.lastIndexOf(")");
                            if (rightParen > leftParen) {
                                poetName = authorPart.substring(0, leftParen).trim();
                                dynasty = authorPart.substring(leftParen + 1, rightParen).trim();
                            } else {
                                poetName = authorPart.trim();
                            }
                        } else {
                            poetName = authorPart.trim();
                        }
                        
                        isReadingContent = true;
                    }
                } 
                // 如果遇到空行，可能是诗的结束
                else if (isReadingContent && line.isEmpty()) {
                    // 保存当前诗
                    if (!title.isEmpty() && !contentLines.isEmpty()) {
                        createAndAddPoem(title, poetName, dynasty, contentLines);
                        poemCount++;
                        contentLines.clear();
                        isReadingContent = false;
                    }
                }
                // 如果在读取内容并且遇到非空行，添加到诗句列表
                else if (isReadingContent && !line.isEmpty()) {
                    contentLines.add(line);
                }
            }
            
            // 处理文件末尾的最后一首诗
            if (isReadingContent && !title.isEmpty() && !contentLines.isEmpty()) {
                createAndAddPoem(title, poetName, dynasty, contentLines);
                poemCount++;
            }
            
            System.out.println("成功从文件加载了 " + poemCount + " 首古诗");
            return poemCount;
        } catch (IOException e) {
            System.err.println("加载古诗文件失败：" + e.getMessage());
            return 0;
        }
    }

    // 创建并添加古诗
    private void createAndAddPoem(String title, String poetName, String dynasty, List<String> contentLines) {
        Poet poet = poets.getOrDefault(poetName, new Poet(poetName, dynasty));
        Poem poem = new Poem(title, poet);
        for (String contentLine : contentLines) {
            poem.addLine(contentLine);
        }
        addPoem(poem);
    }
}